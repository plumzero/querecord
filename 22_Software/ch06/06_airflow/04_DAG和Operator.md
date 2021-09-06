
DAG 定义一个作业流，Operators (称为任务处理器)则定义了实际需要执行的作业。通过将 DAGs 和 Operators 结合起来，用户就可以创建各种复杂的工作流(workflow)。

### Operator

airflow 提供了许多 Operators 来指定我们需要执行的作业，常用的如下:
* `BashOperator`: 执行 bash 命令或脚本
* `PythonOperator`: 调用 python 代码
* `EmailOperator`: 发送邮件
* `HTTPOperator`: 发送 HTTP 请求
* `PostgresOperator`: 发送 SQL 命令
除了这些之外，还有更多的特定处理器: `SSHOperator`、`MySqlOperator`、`SqliteOperator`、`DockerOperator` 等。此外，还可以方便的自定义 Operators 满足个性化的任务需求。


### DAG

