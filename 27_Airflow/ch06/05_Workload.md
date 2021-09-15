
[参考](https://airflow.apache.org/docs/apache-airflow/2.1.3/security/workload.html)

本主题会对如何安全配置 worker 实例进行说明。

### 模仿

基于 task 的 `run_as_user` 参数，Airflow 能够在运行 task 实例时模仿一个 unix 系统用户。

> 注意: 为了实现这种模仿，Airflow 必须以 `sudo` 方式运行，这样子任务会以 `sudo -u` 方式运行，同时文件的权限也会改变。此外，这个 unix 系统用户需要存在于 worker 上。


为了避免那些没有采用模仿机制的任务以 `sudo` 权限运行，如果 `run_as_user` 未设置的话，可以在配置中设定一个缺省的模仿者:
```cfg
    [core]
    default_impersonation = airflow
```
