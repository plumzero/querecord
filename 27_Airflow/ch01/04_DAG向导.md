
[参考](https://airflow.apache.org/docs/apache-airflow/2.1.3/tutorial.html)

该主题主要简单带你了解在使用 Airflow 时写 `Pipeline` 会遇到的一些基本的概念、对象以及它们的用法。

Pipeline 在 Airflow 是一个很重要的概念，它其实就是用于定义一个 Airflow DAG 对象的一个 Python 脚本。这个脚本也可以称为 DAG 定义文件。

以这个[DAG定义文件](t/tutorial.py)作为示例。


### 关于 DAG 文件 

乍看这个脚本文件就像一个配置文件，只是它以代码的形式指定了 DAG 的结构。而在脚本中所定义的任务将会运行在一个与这个脚本文件不一样的上下文环境里。不同的任务适时地运行在不同节点的 worker 进程中，也就意味着这个脚本不能被用作跨任务通信。

可以这样理解，如果你想要定义两个任务，其中一个任务的部分输出将会作为另一个任务的输入。为了实现这种联系，你可以将这两个任务放在同一个 DAG 文件中。否则，就必须使用[XComs](https://airflow.apache.org/docs/apache-airflow/stable/concepts/xcoms.html)挂机来实现跨脚本通信。

有的使用者会将 DAG 定义文件单纯地用作数据处理，但事实并非如此。这个脚本文件的目的是为了定义一个 DAG 对象，它需要以秒级时间创建，因为调度器 scheduler 周期性地将变化进行反映到这个对象上。而如果将其用作数据处理的话，很可能需要消耗可观的时间。


### 引入模块

Airflow Pipeline 就是一个 Python 脚本，可以用来定义一个 Airflow DAG 对象。

在定义一个 DAG 对象时，需要引入一些模块。如下示例:
```py
    from datetime import timedelta
    from textwrap import dedent

    # DAG 对象: 用于实例化一个 DAG
    from airflow import DAG

    # Operators: 需要这些来操作
    from airflow.operators.bash import BashOperator
    from airflow.utils.dates import days_go
```


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
`default_args` 也是 `BaseOperator` 的参数，BaseOperator 会。


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


