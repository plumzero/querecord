
### 检查浏览器是否支持 WebSocket

```js
    if (window.WebSocket) {
        console.log('support')
    } else {
        console.log('unsupport')
    }
```

### WebSocket 对象

创建 WebSocket 对象的参数是需要连接的服务器端的地址，WebSocket 协议的 URL 以 `ws://` 开头，安全的 WebSocket 协议以 `wss://` 开头。
```js
    ws = new WebSocket('ws://echo.websocket.org/');
```
当 Web 应用程序调用 `new WebSocket(url)` 接口时，Browser 就开始了与地址为 url 的 WebSocket 服务器建立握手连接的过程。

WebSocket 对象一共支持四个消息 `onopen`、`onmessage`、`onclose`、`onerror`。

1. 当 Browser 和 WebSocket 服务器连接成功后，会触发 `onopen` 消息:
   ```js
    ws.onopen = function(evt) { }
   ```

2. 如果连接失败，发送、接收数据失败或者处理数据出现错误，Browser 会触发 `onerror` 消息:
   ```js
    ws.onerror = function(evt) { }
   ```

3. 当 Browser 接收到 WebSocket 服务器发送过来的数据时，就会触发 `onmessage` 消息:
   ```js
    ws.onmessage = function(evt) { }
   ```
4. 当 Browser 接收到 WebSocket 服务器发送的关闭连接请求，就会触发 `onclose` 消息:
   ```js
    ws.onclose = function(evt) { }
   ```