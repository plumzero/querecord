
`Flower`  是一个基于 Web 的用于监控和管理 Celery 集群的工具。

本主题会对 Flower 实例的安全进行配置。

### Flower Authentication

Celery Flower 支持 BA 认证，而使用者可以通过启动时命令行传参或者配置文件参数来实现这种认证。

命令行传参:
```sh
    airflow$ airflow celery flower --basic-auth=user1:password1,user2:password2
```

配置参数:
```cfg
    [celery]
    flower_basic_auth = user1:password1,user2:password2
```
