
DIGEST 认证同样使用质询/响应(challenge/response)的方式，但不会像 BASIC 认证那样直接发送明文密码。

所谓质询响应方式是指，一开始一方会先发送认证要求给另一方，接着使用从另一方那接收到的质询码计算生成响应码。最后将响应码返回给对方进行认证的方式。


### DIGEST 认证流程

1. 发送请求
  ```http
    GET /private/ HTTP/1.1
    Host: fangyi.com
  ```

2. 发送临时的质询码(随机数, nonce)以及告知需要认证的状态码 401
   ```http
    HTTP/1.1 401 Authorization Required
    WWW-Authenticate: Digest realm="DIGEST",nonce="MOSQZ0itBAA=44abb6784cc9cbfc605a5b0893d36f23de95fcff",algorithm=MD5,qop="auth"
   ```
   如果服务端要求进行 DIGEST 认证，会返回带 WWW-Authenticate 首部字段的响应。

3. 发送摘要以及由质询计算出的响应码(response)
   ```http
    GET /digest/ HTTP/1.1
    Host: fangyi.com
    Authorization: Digest username="guest",realm="DIGEST",nonce="MOSQZ0itBAA=44abb6784cc9cbfc605a5b0893d36f23de95fcff",uri="/digest/",algorithm=MD5,response="df56389ba3f7c52e9d7551115d67472f",qop=auth,nc=000000001,cnonce="082c875dcb2ca740"
   ```

4. 认证成功返回状态码 200，失败则再次发送状态码 401
   ```http
    HTTP/1.1 200 OK
    Authentication Info: rspauth="f218e9ddb407a3d16f2f7d2c4097e900",cnonce="082c875dcb2ca740",nc=000000001,qop=auth
   ```

DIGEST 认证提供防止密码被窃听的保护机制，但并不存在防止用户伪装的保护机制。虽然提供了高于 BASIC 认证的安全等级，但仍达不到多数 Web 网站对高度安全等级的标准要求。
