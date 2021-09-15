
进入数据库 airflow 中，里面有个表 `ab_role`，查看:
```sh
    airflow=> select * from ab_role;
    id |  name  
    ---+--------
    1  | Admin
    2  | Public
    3  | Viewer
    4  | User
    5  | Op
    (5 rows)
```
这是 Airflow 缺省定义的 5 个角色，你也可以根据需要创建自己的角色。

在启动 web 服务之前，需要根据这些角色创建对应权限的用户进行登录。

这里以创建一个 `Admin` 角色用户和一个 `Viewer` 角色用户作为示例:
```sh
    airflow$ airflow users create --username libei --firstname li --lastname bei --email libei@email.com --role Admin --password admin123
    Admin user libei created

    airflow$ airflow users create --username 郭靖 --firstname 郭 --lastname 靖 --email song@email.com --role Viewer --password viewer123
    Viewer user 郭靖 created
```
注意，一个邮箱只能创建一个用户。

连接 airflow 数据库，查看 `ab_user` 和 `ab_user_role` 表:
```sh
    airflow=> select id, first_name, last_name, username, changed_on, active, email, created_on from ab_user;
    id | first_name | last_name | username |         changed_on         | active |      email      |         created_on         
    ----+------------+-----------+----------+----------------------------+--------+-----------------+----------------------------
    1 | li         | bei       | libei    | 2021-08-31 22:43:21.98106  | t      | libei@email.com | 2021-08-31 22:43:21.981051
    2 | 郭         | 靖        | 郭靖     | 2021-08-31 22:52:36.196941 | t      | song@email.com  | 2021-08-31 22:52:36.196932
    (2 rows)

    airflow=> select * from ab_user_role;
    id | user_id | role_id 
    ----+---------+---------
    1 |       1 |       1
    2 |       2 |       3
    (2 rows)
```

好了，现在可以启动 webserver 了:
```sh
    airflow$ airflow webserver -p 8080
    ____________       _____________
    ____    |__( )_________  __/__  /________      __
    ____  /| |_  /__  ___/_  /_ __  /_  __ \_ | /| / /
    ___  ___ |  / _  /   _  __/ _  / / /_/ /_ |/ |/ /
    _/_/  |_/_/  /_/    /_/    /_/  \____/____/|__/
    [2021-09-06 15:12:37,294] {dagbag.py:496} INFO - Filling up the DagBag from /dev/null
    Running the Gunicorn Server with:
    Workers: 4 sync
    Host: 0.0.0.0:8080
    Timeout: 120
    Logfiles: - -
    Access Logformat: 
    =================================================================            
    [2021-09-06 15:12:41 +0800] [15109] [INFO] Starting gunicorn 20.1.0
    [2021-09-06 15:12:41 +0800] [15109] [INFO] Listening at: http://0.0.0.0:8080 (15109)
    [2021-09-06 15:12:41 +0800] [15109] [INFO] Using worker: sync
    [2021-09-06 15:12:41 +0800] [15111] [INFO] Booting worker with pid: 15111
    [2021-09-06 15:12:41 +0800] [15112] [INFO] Booting worker with pid: 15112
    [2021-09-06 15:12:42 +0800] [15113] [INFO] Booting worker with pid: 15113
    [2021-09-06 15:12:42 +0800] [15114] [INFO] Booting worker with pid: 15114
```
如果需要在后台启动，可以加上参数 `-D`。

在浏览器地址栏中输入如下 url 访问(192.168.3.40 是 Airflow webserver 进程机器地址):
```sh
    http://192.168.3.40:8080
```

顺利的话，输入用户名和密码就可以访问了。