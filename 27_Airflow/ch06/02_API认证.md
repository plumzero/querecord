
[参考: API](https://airflow.apache.org/docs/apache-airflow/2.0.2/security/api.html)

### Airflow 的 API 认证

API 认证操作与 Web 认证是分离开来的。

缺省时 API 认证时会拒绝所有请求，这从 airflow 配置中可见端倪:
```cfg
    [api]
    auth_backend = airflow.api.auth.backend.deny_all
```

你也可以通过命令行方式查看当前 API 认证状态:
```sh
    airflow$ airflow config get-value api auth_backend
```

### 禁用认证

如果你想让试验性API(`experimental API`，与之对立的是 `stable REST API`)工作起来，同时对这样操作的风险性有所觉悟，那么你可以在配置中像下面这样禁用 API 认证:
```cfg
    [api]
    auth_backend = airflow.api.auth.backend.default
```
注意，上面的配置无法禁用对 stable REST API 认证。


### Basic Authentication

API 支持基于用户密码方式的 BA 认证。

为了开启 BA 认证，需要修改一下配置。如下:
```cfg
    [api]
    auth_backend = airflow.api.auth.backend.basic_auth
```
BA 认证会对用户名和密码进行 base64 编码，并将编码值放到 HTTP 头的 `Authorization` 中，可以想见，这是一种不安全的认证方式。

> 操作演示: 首先使用缺省认证(deny_all)发送 API 请求，之后再开启 BA 认证发送同样的请求，最后在 BA 认证状态下以不同的用户身份发送相同的请求。观察结果。
1. deny_all 认证下发送下面的请求:
   ```sh
    curl -X GET --user "libei:admin123" http://192.168.3.40:8080/api/v1/pools
   ```
   输出结果如下:
   ```sh
    {
    "detail": null,
    "status": 401,
    "title": "Unauthorized",
    "type": "https://airflow.apache.org/docs/apache-airflow/2.1.3/stable-rest-api-ref.html#section/Errors/Unauthenticated"
    }
   ```
   可以看到，认证不通过。
2. 开启 basic_auth 认证后，发送上面同样的请求，输出结果如下:
   ```sh
    {
    "pools": [
        {
        "name": "default_pool",
        "occupied_slots": 0,
        "open_slots": 128,
        "queued_slots": 0,
        "running_slots": 0,
        "slots": 128
        }
    ],
    "total_entries": 1
    }
   ```
   认证通过，并返回了结果。
3. 在前面的测试中，是以 Admin 角色用户身份发送请求的。可以想像地，Admin 角色当然有权限对上面的接口进行访问。这时，如果换成 Viewer 角色呢？执行:
   ```sh
    curl -X GET --user "YangGuo:viewer123" http://192.168.3.40:8080/api/v1/pools
   ```
   输出结果如下:
   ```sh
    {                                                                                                                        
    "detail": null,                                                                                                        
    "status": 403,                                                                                                         
    "title": "Forbidden",                                                                                                  
    "type": "https://airflow.apache.org/docs/apache-airflow/2.1.3/stable-rest-api-ref.html#section/Errors/PermissionDenied"
    }                                                                                                                        
   ```
   可以看到，这次不是认证不通过，而不权限禁止。即 Viewer 角色用户无法访问这个接口资源。
4. 事实上，上面带有 `/api/v1` 形式的 URL 就是所谓的试验性 API。如果将 `/api/v1` 去掉，比如将上面的 `/api/v1/pools` 变成 `/pools`，就变成了所谓的 `stable REST API`。
   ```sh
    curl -X GET --user "libei:admin123" http://192.168.3.40:8080/pools
   ```
   输出结果如下:
   ```html
    <!DOCTYPE html>
    <html lang="en">
    <head>
    <title>Airflow 404 = lots of circles</title>
    <link rel="icon" type="image/png" href="/static/pin_32.png">
    </head>

    <body>
        <div style="font-family: verdana;">
            <h1>Airflow 404 = lots of circles</h1>
            <p>ubuntu</p>
        </div>
        <div id="div_svg"
            class="centered text-center"
            style="border: 1px solid #ccc;padding:0;margin:0;">
            <svg id="circles-svg"></svg>
        </div>
        <script src="/static/dist/circles.995e0afd45c3641109e1.js"></script>
    </body>
   ```
   提示无法访问到这个资源，说明即使 BA 认证也是无法访问 stable REST API 资源的。

### Stable API Permissions

关于 Stable API 的权限，有 `endpoint` 的概念。比如上面的 `/pools` 就是一个 endpoint 的，每个 endpoint 会限定特定角色进行访问。
