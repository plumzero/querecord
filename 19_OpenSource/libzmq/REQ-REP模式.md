
## REQ-REP 模式

REQ-REP 模式是阻塞式的，即必须 client 先发送一条请求(REQuest)给 server，然后 server 才可以返回一个回应(REPly)给 client。任何顺序上的错误都会导致报错。

服务端进程代码示例如下:
```c++
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    zmq::message_t request;
    socket.recv(&request);
    
    std::string msg((const char *)request.data(), request.size());
    printf("Server received request: %s\n", msg.c_str());
    printf("Now Server would take 2 seconds to deal with message.\n");
    sleep(2);
    
    char rep[] = { "Server sent this message" };
    zmq::message_t reply(rep, strlen(rep));
    socket.send(reply);
```

客户端进程代码示例如下:
```c++
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    socket.connect("tcp://localhost:5555");
    
    printf("Client would send a request to Server.\n");
    
    char req[] = { "Client sent this message" };
    zmq::message_t request(req, strlen(req));
    socket.send(request);
    
    zmq::message_t reply;
    socket.recv(&reply);
    
    std::string msg((const char *)reply.data(), reply.size());
    printf("Client received reply: %s\n", msg.c_str());
```

看起来和直接调用 Posix 的 `send` 或 `recv` 接口发送或接收差不多。

使用 Posix 接口实现的简易 Server，接收了一个 Client 连接之后，接下来会处理这个客户端发来的数据。如果这时另一个 Client 也尝试连接 Server 的话，会失败，因为 Server 进程此时已经执行过了 `accept` 代码。

但是通过 zmq 实现的简易 Server 却可以同时接受多个 Client 的连接，原因就是 zmq 将 `accept` 线程与 `send/recv` 线程分离了。在哪里创建的另一个线程呢？如下:
```c++
    zmq::context_t context(1);
```
参数 1 就表示新创建一个子线程。

所以，服务端进程如果需要处理多个客户端连接时，可以这样修改:
```c++
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    
    while (true) {
        zmq::message_t request;
        socket.recv(&request);
        
        std::string msg((const char *)request.data(), request.size());
        printf("Server received request: %s\n", msg.c_str());
        printf("Now Server would take 2 seconds to deal with message.\n");
        sleep(2);
        
        char rep[] = { "Server sent this message" };
        zmq::message_t reply(rep, strlen(rep));
        socket.send(reply);
    }
```
测试程序为 `simpleclient.cpp` 和 `simpleserver.cpp` 。

----
接下来要测试服务端在 `zmq::context_t` 中指定参数创建多个线程时的效率比较。
测试程序为 `req_rep_client.cpp` 和 `req_rep_server.cpp` 。

在 4 核虚拟机上运行测试，对 `req_rep_server.cpp` 中的 `zmq::context_t` 进行不同设置，测试结果如下:
```shell
    zmq::context_t  cost_time
    1               13667
    4               22300
```

至于 `zmq::context_t` 中创建的线程，是用于 `accept` 还是用于 `send/recv`，这个暂时是未知的。
