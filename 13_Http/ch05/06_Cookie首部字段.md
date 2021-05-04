
Cookie 的工作机制是用户识别及状态管理。Web 网站为了管理用户的状态会通过 Web 浏览器，把一些数据临时写入用户的计算机内。接着当用户访问该 Web 网站时，可通过通信方式取回之前发送的 Cookie 。

为 Cookie 服务的首部字段有两个:

|    首部字段名    | 说明   | 首部类型 |
|:----------------|:-------|:--------|
| [Set-Cookie](#Set-Cookie) | 开始状态管理所使用的 Cookie 信息 | 响应首部字段 |
| [Cookie](#Cookie)         | 服务器接收到的 Cookie 信息       | 请求首部字段 |


### Set-Cookie

示例:
```shell
    Set-Cookie: status=enable; expires=Tue, 04 May 2021 10:53:56 GMT; path=/; domain=libeio.com;
```
当服务器准备开始管理客户端的状态时，会事先像上面这样告知客户端各种信息。

Set-Cookie 字段的属性

| 属性        | 说明   |
|:-----------|:-------|
| NAME=VALUE | 赋予 Cookie 的名称及其值(必需项) |
| expires=DATE | Cookie 的有效期(若不明确指定则默认为浏览器关闭前为止) |
| path=PATH | 将服务器上的文件目录作为 Cookie 的适用对象(若不指定则默认为文档所在的文件目录) |
| domain=域名 | 作为 Cookie 适用对象的域名(若不指定则默认为创建 Cookie 的服务器的域名) |
| Secure | 仅在 HTTPS 安全通信时才会发送 Cookie |
| HttpOnly | 加以限制，使 Cookie 不能被 JS 脚本访问 |


### Cookie

首部字段 Cookie 会告知服务器，当客户端想获得 HTTP 状态管理支持时，就会在请求中包含从服务器接收到的 Cookie。接收到多个 Cookie 时，同样可以以多个 Cookie 形式发送。
