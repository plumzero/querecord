
Web 应用是指通过 Web 功能提供的应用程序。

原本应用 HTTP 协议的 Web 的机制就是对客户端发来的请求，返回事前准备好的内容。可随着 Web 越来越普及，仅靠这样的做法已不足以应对所有的需求，更需要引入由程序创建 HTML 内容的做法。

类似这种由程序创建的内容称为动态内容，而事先准备好的内容称为静态内容。Web 应用则作用于动态内容之上。


### CGI

CGI(Common Gateway Interface，通用网关接口)是指 Web 服务器在接收到客户端发送过来的请求后转发给其他处理程序的一组机制。在 CGI 的作用下，程序会对请求内容做出相应的动作，比如创建 HTML 等动态内容。

CGI 程序可以通过 Perl、PHP、Ruby 和 C 等编程语言编写而成。


### Servlet

Servlet (SERVer appLET，轻量服务程序)是一种能在服务器上创建动态内容的程序。Servlet 是用 Java 语言实现的一个接口，属于面向企业级 Java(JavaEE, Java Enterprise Edition)的一部分。

由于 CGI 程序与 Web 应用位于不同的进程中，所以 Web 应用每次接到请求时，都需要运行一次 CGI 程序或与其进行进程间通信。一旦访问量过大，Web 服务器就要承担相当大的负载。而 Servlet 运行在与 Web 服务器相同的进程中，因此受到的负载较小。

Servlet 的运行环境叫做 Web 容器或 Servlet 容器。
