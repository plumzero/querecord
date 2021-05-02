
WWW 定义了3个重要的概念，它们分别是访问信息的手段与位置(URI, Uniform Resource Identifier)、信息的表现形式(HTML, HyperText Markup Language)以及信息转发(HTTP, HyperText Transfer Protocol)等操作。

通过 JavaScript 可以在浏览器端和服务端执行特定的程序以实现更加精彩、多样的内容。


### URI

URI 是一种可以用于 WWW 之外的高效识别码，它被用于主页地址、电子邮件、电话号码等各种组合中。如下所示:
```shell
    http://www.rfc-editor.org/rfc/rfc4395.txt
    http://www.ietf.org:80/index.html
    http://localhost:631/
```
上面这些例子属于一般主页地址，也被叫做 URL(Uniform Resource Locator)。URL 常被用来表示互联网中资源(文件)的具体位置。但是 URI 不局限于标识互联网资源，它可以作为所有资源的识别码。URI 可以用于除了 WWW 之外的其他应用协议中。


### HTML

HTML 是 WWW 的一种数据表现格式，可以在 Web 页中展现文件、图像、链接等内容。


### HTTP

当用户在浏览器的地址栏里输入所要访问 Web 页的 URI 以后，HITP 的处理即会开始。HTTP 默认使用 80 端口。它的工作机制，首先是客户端向服务器的 80 端口建立一个 TCP 连接，然后在这个 TCP 连接上进行请求和应答以及数据报文的发送。

HTTP 中常用的有两个版本，一个是 HTTP1.0，另一个是 HTTP1.1。两者的主要区别是在 1.0 版本中每一个请求和响应都会触发一次 TCP 连接的建立和断开，而从 1.1 开始，允许在一个 TCP 连接上进行多个请求和响应(keep-alive, 长连接)。由此，大大地减少了 TCP 连接的建立和断开操作，从而提高了传输效率。


### JavaScript

Javascript 是一种嵌入在 HTML 中的编程语言，作为客户端程序它可以运行于多种类型的浏览器中。这些浏览器将嵌入 JavaScript 的 HTML 加载后，其对应的 JavaScript 程序就可以在客户端得到执行。

JavaScript 程序可用于验证客户端输入字符串是否过长、是否填写或选择了页面中的必须选项等功能。还可以用于操作 HTML 或 XML 的逻辑结构(DOM, Document Object Model)以及动态显示 Web 页的内容和页面风格。

现在，通过 Ajax(Asynchronous JavaScript and XML)技术可以使服务端不需要读取整个页面而是通过 JavaScript 操作 DOM 来实现更为生动的 Web 页面技术。


### CGI

CCI(Common Gateway Interface)是 Web 服务器调用外部程序时所使用的一种服务端应用的规范。

一般的 Web 通信中．只是按照客户端请求将保存在 Web 服务器硬盘中的数据进行转发，这种情况下客户端每次收获的信息是同样(静态)的内容。而引入 CGI 以后客户端端请求会触发 Web 服务器端运行另一个程序，客户端所输人的数据也会传给这个外部程序。该程序运行结束后会将生成的 HTML 和其他数据再返回给客户端。

利用 CGI 可以针对用户的操作给客户端返回各种各样变化(动态)的信息。论坛和网上购物系统中就经常使用 CCI 调用外部程序或访问数据库。


### Cookie

Web 应用中为了获取用户信息使用一个叫做 Cookie 的机制。Web服务器用 Cookie 在客户端保存信息(多为"用户名"和"登录名"等信息)。Cookie 也常被用于保存登录信息或网络购物中放入购物车的商品信息。

从 Web 服务器检查 Cookie 可以确认是否为同一对端的通信。
