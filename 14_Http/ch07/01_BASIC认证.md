
### BASIC 认证流程

1. 发送请求
  ```http
    GET /private/ HTTP/1.1
    Host: fangyi.com
  ```

2. 服务端返回状态码 401 以告知客户端需要进行认证
  ```http
    HTTP/1.1 401 Authorization Required
    Date: Tue, 4 May 2021 16:45:23 GMT
    Server: Apache/3.2.1
    WWW-Authenticate: Basic realm="Input Your ID and Password."
  ```

3. 用户 ID 和密码以 Base64 方式编码后发送
   ```http
    GET /private/ HTTP/1.1
    Host: fangyi.com
    Authorization: Basic Z3Vic3Q6Z3Vic3Q
   ```

4. 认证成功者返回状态码 200，若认证失败则返回状态码 401
  ```http
    HTTP/1.1 200 OK
    Date: Tue, 4 May 2021 16:48:55 GMT
    Server: Apache/3.2.1
  ```

BASIC 认证因其安全性问题一般并不常用于互联网中。
