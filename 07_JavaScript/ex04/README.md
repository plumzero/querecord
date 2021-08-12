
### 学习目标

* 了解 Ajax 的概念
* 了解 Ajax 的原理


### Ajax 的概念

Ajax 全称 叫 Asynchronous JavaScript and XML，意思是异步的 JavaScript 和 XML。它的主要优势就是对页面的请求以异步方式发送到服务器，而服务器不会用整个页面来响应请求，它会在后台处理请求，与此同时用户还能继续浏览页面并与页面交互。


### Ajax 的原理

Ajax 技术的核心就是 `XMLHttpRequest` 对象。这个对象充当着浏览器中的脚本(客户端)与服务器之间的中间人的角色。以往的请求都由浏览器发出，而 JavaScript 通过这个对象可以自己发送请求，同时也自己处理响应。

Ajax 的运行过程包括以下几个方面:
1. 浏览器通过事件触发方法，本地通过 `XMLHttpRequest` 对象，创建并且发送请求通过互联网到服务器
2. 服务器收到请求的内容，响应请求，发送所需数据到浏览器
3. 浏览器通过 XMLHttpRequest 对象的 `onreadystatechange` 的方法收到请求的数据后，解析和渲染数据到页面中。

Ajax 依赖的标准有以下几个:
* XMLHttpRequest 对象，异步的与服务器交换数据
* JavaScript/DOM，信息显示/交互
* XML，作为转换数据的格式


### XMLHttpRequest 的使用

1. 创建 XMLHttpRequest 对象，通过 `new` 实例化一个 XMLHttpRequest 对象。
   ```js
    var xhr = new XMLHttpRequest() || new ActiveXObject("Microsoft.XMLHTTP");   // 兼容 ie
   ```
2. 利用 `open` 方法发起请求
   `open(method, url, async)` 接受三个参数。
   * method 表示请求的类型，如 `get` 和 `post`。
   * url 是请求的资源在服务端中的地址。
   * async 指示是否按异步方式处理请求，取值可以是 `true` 和 `false`。
   GET 异步请求示例:
   ```js
    xhr.open("get", "http://192.168.2.102:8080/api/v1/red", true);
   ```
   如果想要利用 GET 方法传递参数，可以在 url 中通过 ? & = 方式传递。注意，对特殊字符要进行编码处理。
3. 利用 `send` 方法发送请求
   `send(string)` 接受的参数为请求类型为 POST 时传递的值，为 GET 类型时候不传值。
   POST 发送请求示例:
   ```js
    xhr.send('tamp=' + Date.parse(new Date()));
   ```
4. 通过 `onreadystatechange` 注册一个回调事件方法用于获取响应的数据信息。
   XMLHttpRequest 的 `readyState` 属性发生变化时，就会触发该事件。其属性值及含义如下:
   * 0: 请求未初始化
   * 1: 服务器连接已建立
   * 2: 请求已接收
   * 3: 请求处理中
   * 4: 请求已完成，且响应已就绪
  XMLHttpRequest 的 `status` 属性可用于查看响应的状态码。
  完整的 POST 请求示例:
  ```js
    var xhr = new XMLHttpRequest() || new ActiveXObject("Microsoft.XMLHTTP");
    xhr.open("get", "http://192.168.2.102:8080/api/v1/red", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");  // 设置请求头
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            console.log(xhr.statusText);                        // 响应行状态
            console.log(xhr.getResponseHeader('Content-Type')); // 内容类型
            console.log(xhr.getAllResponseHeaders());           // 所有响应头
            if (xhr.status === 200) {
                console.log(xhr.responseText);                  // 字符串形式的响应信息
                console.log(xhr.responseXML);                   // XML Document 形式的响应信息
            }
        }
    };
    xhr.send("key=value");
  ```
