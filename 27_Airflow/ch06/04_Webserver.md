
[参考](https://airflow.apache.org/docs/apache-airflow/2.1.3/security/webserver.html)

本主题会对如何安全配置 Webserver 实例进行说明。

### 开启框架禁用

缺省时，在一个网页框架中是可以使用 Airflow 的，(为了防止点击劫持攻击)可以通过如下配置禁用:
```cfg
    [webserver]
    x_frame_enabled = False
```

### Web 认证

1. BA 认证

缺省时，Airflow 要求用户在登录之前进行密码认证。比如可以通过如下命令创建一个用户:
```sh
    airflow$ airflow users create --username admin --firstname Peter --lastname Parker --role Admin --email spiderman@superhero.org
```

2. 匿名登录

如果想要跳过认证，以匿名身份登录，可以通过修改 `$AIRFLOW_HOME/webserver_config.py` 文件中的如下字段来实现:
```py
    AUTH_ROLE_PUBLIC = 'Admin'
```
修改完成后，在浏览器地址栏中输入 `web-host-ip:8080`，它会以 Admin 角色身份匿名登录。

经测试发现，目前只能通过 Admin 角色进行匿名登录，直观上感觉是一次危险的尝试。

3. 其他方式

略
