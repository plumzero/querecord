
[参考](https://airflow.apache.org/docs/apache-airflow/2.1.3/concepts/dags.html)

DAG(Directed Acyclic Graph) 是 Airflow 的核心概念，它是 task 的容器，并组织它们运行。

以下面的简单 DAG 示例:

![](img/basic-dag.png)

这里定义了 4 个 task，并规定了它们的运行组织方式。

DAG 自身不必关心它所包含的每个任务发生了什么，只需要简单考虑应该以何种方式(如规定顺序)运行它们，或者多久之后重新运行它们。

### 声明 DAG

有三种方式声明一个 DAG。

一种是使用上下文管理器，它会将 DAG 的所有东西隐式添加到管理器中:
```py
    with DAG("my_dag_name") as dag:
        op = DummyOperator(task_id="task") 
```

一种是使用标准的构造器，将 dag 传入到指定的 Operator 中:
```py
    my_dag = DAG("my_dag_name")
    op = DummyOperator(task_id="task", dag=my_dag)
```

一种是使用 `@dag` 修饰器，将函数转为一个 DAG 生成器:
```py
    @dag(start_date=days_ago(2))
    def generate_dag():
        op = DummyOperator(task_id="task")

    dag = generate_dag()
```

只有定义了要运行的 task，DAG 才有意义。task 通常以 Operator、Sensors 或 TaskFlow 形式出现。

### 任务依赖

一个 DAG 中通常并不仅仅包含一个 Task/Operator。它们各自可能是一些任务的上游任务，同时又作为另一些任务的下游而存在，对这些任务之间依赖关系的定义，就构成了有向无环图 DAG 的"边"。

有两种方式定义每个单独任务之间的这种依赖。推荐使用 `>>` 和 `<<` 操作符:
```py
    first_task >> [second_task, third_task]
    third_task << fourth_task
```

当然，也可以通过 `set_upstream` 和 `set_downstream` 方法:
```py
    first_task.set_downstream([second_task, third_task])
    third_task.set_upstream(fourth_task)
```

如果你想让一个列表中的 task 依赖于另一个列表中的 task，上面的方法不再行得通，此时需要使用 `cross_downstream`:
```py
    from airflow.models.baseoperator import cross_downstream

    # Replaces
    # [op1, op2] >> op3
    # [op1, op2] >> op4
    cross_downstream([op1, op2], [op3, op4])
```

如果你想对 task 进行串联，可以使用 `chain`:
```py
    from airflow.models.baseoperator import chain

    # Replaces op1 >> op2 >> op3 >> op4
    chain(op1, op2, op3, op4)

    # You can also do it dynamically
    chain([DummyOperator(task_id='op' + i) for i in range(1, 6)])    
```
`chain` 也可以组成同尺寸列表成对依赖(还是看代码吧):
```py
    from airflow.models.baseoperator import chain

    # Replaces
    # op1 >> op2 >> op4 >> op6
    # op1 >> op3 >> op5 >> op6
    chain(op1, [op2, op3], [op4, op5], op6)
```


### 加载 DAG

Airflow 从 Python 资源文件中加载 DAG，Python 文件位于 DAG_FOLDER 路径下。它会获取每个文件，执行并从文件中加载 DAG 对象。

你可以在单个 Python 文件中定义多个 DAG，甚至可以使用 `import` 将一个复杂的 DAG 分散在多个 Python 文件中。

注意，虽然 Airflow 可以从单个 Python 文件中加载多个 DAG 对象，但它只会加载顶格的 DAG 并实例化。如下示例:
```py
    def my_function():
        dag_2 = DAG('but_this_dag_will_not')

    dag_1 = DAG('this_dag_will_be_discovered')

    my_function()
```
dag_1 位于顶格，会被加载到 Airflow 中，而 dag_2 就不会。

在 DAG_FOLDER 路径下，你可以创建一个 `.airflowignore` 文件用于忽略对某些文件的获取。

### 运行 DAG

DAG 以两种方式之一种运行:
* 通过 UI 按钮手动或者通过 API 触发
* 由调度器调度执行

DAG 并不需要调度(毕竟调度的对象是 task 啊)，但通常也会定义一个，这通过参数 `schedule_interval` 来实现:
```py
    with DAG("my_daily_dag", schedule_interval="@daily"):
        ...
```
schedule_interval 参数支持 crontab 语义，所以你可以像下面这样定义:
```py
    with DAG("my_daily_dag", schedule_interval="0 * * * *"):
        ...
```

每次在运行 DAG 时，都会创建一个实例，Airflow 将其称之为 `DAG Run`。由同一个 DAG 产生的 DAG Runs 可以并行运行，每个 DAG Run 都会定义一个 `execution_date`，它标识了运行到的逻辑日期和时间。

DAG Run 的概念很有用，试想一下，有一个处理每日试验数据的 DAG，现在要把它重写为运行处理三个月之前的数据。这没有问题，因为 Airflow 可以通过补录(backfill)方式一次性完成对过去三个月每一天执行一次 DAG 的副本。这些 DAG Runs 虽然是在同一天开始运行的，但是它们的 execution_date 值将涵盖过去三个月，这个值也是 DAG 中的所有 tasks/operators/sensors 在运行时所要查看的内容。

DAG 在每次运行时会实例化为一个 DAG Run，同样地，DAG 中的 Task 在每次运行时也会实例化为一个 `Task Instances`。


### Default Arguments

同一个 DAG 中的很多 Operator 往往使用一组相同的缺省参数(比如 start_date)。为了避免为每个 Operator 一个一个地指定这些参数，你可以为 DAG 传入 `default_args` 参数，它会将其自动与 Operator 绑定:
```py
    default_args = {
        'start_date': datetime(2016, 1, 1),
        'owner': 'airflow'
    }

    with DAG('my_dag', default_args=default_args) as dag:
        op = DummyOperator(task_id='dummy')
        print(op.owner)  # "airflow"
```

### DAG 装饰器

除了通过 DAG() 声明一个 DAG 这种传统方式之外，自版本 2.0 起，你也可以通过 `@dag` 装饰器将一个普通的函数转化为一个 DAG 生成器函数。
```py
    @dag(default_args=DEFAULT_ARGS, schedule_interval=None, start_date=days_ago(2), tags=['example'])
    def example_dag_decorator(email: str = 'example@example.com'):
        """
        DAG to send server IP to email.

        :param email: Email to send IP to. Defaults to example@example.com.
        :type email: str
        """
        get_ip = GetRequestOperator(task_id='get_ip', url="http://httpbin.org/get")

        @task(multiple_outputs=True)
        def prepare_email(raw_json: Dict[str, Any]) -> Dict[str, str]:
            external_ip = raw_json['origin']
            return {
                'subject': f'Server connected from {external_ip}',
                'body': f'Seems like today your server executing Airflow is connected from IP {external_ip}<br>',
            }

        email_info = prepare_email(get_ip.output)

        EmailOperator(
            task_id='send_email', to=email, subject=email_info['subject'], html_content=email_info['body']
        )


    dag = example_dag_decorator()
```

### 流的控制 Control Flow

缺省地，task 会等待上游所有的任务运行成功之后才开始执行，但也可以通过如下方式改变这种机制。

1. Branching

基于某种条件选择哪些任务要移动。

使用 Branching 方式可以告知 DAG 不要运行所有依赖的上游任务，只是选择一个或几个执行。其通过 BranchPythonOperator 实现。

`BranchPythonOperator` 很像 PythonOperator，只不过它期望一个能够返回一个(或一组)`task_id` 的 `python_callable`。接下来会执行这个(或些) `task_id` 所标识的 task，其他的则被跳过。 




2. Latest Only

Branching 的一种特殊形式，

3. Depends On Past

4. Trigger Rules



