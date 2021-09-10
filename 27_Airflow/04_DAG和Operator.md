
[参考](https://airflow.apache.org/docs/apache-airflow/stable/tutorial.html)

DAG 定义一个作业流，Operators (称为任务处理器)则定义了实际需要执行的作业。通过将 DAGs 和 Operators 结合起来，用户就可以创建各种复杂的工作流(workflow)。

airflow 提供了许多 Operators 来指定我们需要执行的作业，常用的如下:
* `BashOperator`: 执行 bash 命令或脚本
* `PythonOperator`: 调用 python 代码
* `EmailOperator`: 发送邮件
* `HTTPOperator`: 发送 HTTP 请求
* `PostgresOperator`: 发送 SQL 命令
除了这些之外，还有更多的特定处理器: `SSHOperator`、`MySqlOperator`、`SqliteOperator`、`DockerOperator` 等。此外，还可以方便的自定义 Operators 满足个性化的任务需求。

关于 Operator，没什么好说的。这里主要对如何编写 DAG 进行说明。

### 关于 DAG 定义文件

以这个[DAG定义文件](t/tutorial.py)作为示例。

乍看这个脚本文件就像一个配置文件，只是它以代码的形式指定了 DAG 的结构。而在脚本中所定义的任务将会运行在一个与这个脚本文件不一样的上下文环境里。不同的任务适时地运行在不同节点的 worker 进程中，也就意味着这个脚本不能被用作跨任务通信。

可以这样理解，如果你想要定义两个任务，其中一个任务的部分输出将会作为另一个任务的输入。为了实现这种联系，你可以将这两个任务放在同一个 DAG 文件中。否则，就必须使用[XComs](https://airflow.apache.org/docs/apache-airflow/stable/concepts/xcoms.html)挂机来实现跨脚本通信。

有的使用者会将 DAG 定义文件单纯地用作数据处理，但事实并非如此。这个脚本文件的目的是为了定义一个 DAG 对象，它需要以秒级时间创建，因为调度器 scheduler 周期性地将变化进行反映到这个对象上。

### 引入模块

airflow pipeline 就是一个 Python 脚本，可以用来定义一个 airflow DAG 对象:
```py
    from datetime import timedelta
    from textwrap import dedent

    # DAG 对象: 用于实例化一个 DAG
    from airflow import DAG

    # Operators: 需要这些来操作
    from airflow.operators.bash import BashOperator
    from airflow.utils.dates import days_go
```
好了，暂时这样理解。利用 Operator 来操作 DAG 对象。

### Default Arguments

现在我们准备创建一个 DAG 文件以及几个任务，这时如果我们想要为每个任务的构造函数显式地传入一组参数(未必都能用到)，就可以定义一个包含默认参数的字典，用于创建任务:
```py
    # defaut_args 中的参数会传递到每个 operator 中，你可以在 operator 初始化时为每个任务重写这些参数
    default_args = {
        'owner': 'airflow',
        'depend_on_past': False,
        'email': ['airflow@example.com'],
        'email_on_failure': False,
        'email_on_retry': False,
        'retries': 1,
        'retry_delay': timedelta(minutes=5),
        # 'queue': 'bash_queue',
        # 'pool': 'backfill',
        # 'priority_weight': 10,
        # 'end_date': datetime(2016, 1, 1),
        # 'wait_for_downstream': False,
        # 'dag': dag,
        # 'sla': timedelta(hours=2),
        # 'execution_timeout': timedelta(seconds=300),
        # 'on_failure_callback': some_function,
        # 'on_success_callback': some_other_function,
        # 'on_retry_callback': another_function,
        # 'sla_miss_callback': yet_another_function,
        # 'trigger_rule': 'all_success'
    }
```
关于上面每个参数的意义，看[这里](https://airflow.apache.org/docs/apache-airflow/stable/_api/airflow/models/index.html)。

这里对几个常用的参数进行说明:

| 参数名称 | 参数类型 | 说明 |
|:--------|:--------|:-----|
| task_id | str     | 作为任务的唯一标识 |
| owner   | str     | 任务的所有者，建议使用 unix 用户，一般是 airflow 用户 |
| description | str | DAG 描述，会显示在 web 页面上 |
| schedule_interval | datetime.timedelta/dateutil.relativedelta.relativedelta/str | 定义 DAG 多长时间执行一次，这个参数会被追加到最近一次执行产生的 execution_date 上以计算出下次调度的时刻 |
| email   | str 或 list[str] | 定义邮件报警的目的地址，可以是一个或多个，多个时以逗号或分号间隔 |
| email_on_retry | bool | 任务重试时，邮件报警是否也要重发 |
| email_on_failure | bool | 任务失败时，是否要发送邮件报警 |
| retries | int | 指定任务的重试测试 |
| retry_delay | datetime.timedelta | 指定两次重试之间的间隔 |
| start_date | datetime.datetime | 指定任务的开始时间 |
| end_date | datetime.datetime | 如果指定了这个参数，在超过这个时间后，调度器将不会对任务进行调度 |
| depends_on_past | bool | 设置为真时，任务实例循序执行，只有当前面的实例成功或被跳过时，才会执行下一个 |
| queue | str | 指定运行作业的队列。未必所有的执行器都实现了队列管理，比如 CeleryExecutor 就不支持 |
| pool | str | 指定任务运行的 slot pool 。用于限制某些任务的并发执行 |
| priority_weight | int | 指定相比于其他任务的优先权重。执行器会优先执行高权重任务 |
| dag | airflow.models.DAG | 对与任务绑定的 dag 对象的引用 |
| execution_timeout | datetime.timedelta | 设定任务实例的最大执行时长，若超时将抛出异常并失败 |
| on_failure_callback | TaskStateChangeCallback | 当一个任务实例失败时，将调用此函数 |
| on_success_callback | TaskStateChangeCallback | 当一个任务实例成功时，将调用此函数 |
| on_retry_callback  | TaskStateChangeCallback | 当一个任务进行触发重试时，将调用此函数 |
| trigger_rule | str | 一般为 all_success |
| tags | list[str] | 用于帮助在 web 页面上过滤 DAG |
| dag_id | str 或 list[str] | 用于查找一个 DAG 对象 |

使用者可以根据自己的意图来定义不同的参数，比如区分生产环境和开发环境。

### 实例化 DAG

我们需要创建一个 DAB 对象来将任务放到里面运行。如下示例中，第一个参数 `tutorial` 即 dag_id 作为唯一标识，同时传入缺省参数集来定义一个执行频率为 1 天的 DAG 对象:
```py
    with DAG(
        'tutorial',
        default_args = default_args,        // 使用系统缺省参数集
        # 以下是重写的参数
        description = 'A simple tutorial DAG',
        schedule_interval = timedelta(days=1),
        start_date=days_ago(2),
        tags = ['example'],
    ) as dag:
```

### 任务

当实例化 operator 对象时，任务就会被创建。我们将上面的参数传入到 operator 中，就可以创建一个任务，而 `task_id` 会作为这个任务的唯一标识:
```py
    t1 = BashOperator(
        task_id = 'print_date',
        bash_command = 'date',
    )

    t2 = BashOperator(
        task_id = 'sleep',
        depends_on_past = False,
        bash_command = 'sleep 5',
        retries = 3,
    )
```
这里在创建任务 t2 时，同时传入了一个针对于 BashOperator 的特定参数 bash_command，以及一个通用参数 retries，后者会对 default_args 中的同名参数进行重写。

参数的优先使用顺序如下:
* 显示入参
* 定义在 default_args 中的参数
* operator 的缺省参数，如果存在的话

一个任务必须包括或者继承 `task_id` 和 `owner` 参数，否则 Airflow 会抛出异常。

### 使用 Jinja 模板

暂略

### 设置依赖

假定现在有 3 个任务，分别是 t1 t2 t3，开始时互不依赖。这里提供了几种方式来定义它们之间的依赖。

t2 依赖 t1，用箭头表示就是 t1 指向 t2。如下两种方式都可以表述这种关系:
```py
    t1.set_downstream(t2)
    t2.set_upstream(t1)
```

上面的不够直观，可以用下面的方式替代:
```py
    t1 >> t2
    t2 << t1
```

其他的依赖方式示例:
```py
    t1 >> t2 >> t3
    t1 >> [t2, t3]
    [t2, t3] >> t1
```

设置依赖时，注意不要形成闭环哟！


### 测试

