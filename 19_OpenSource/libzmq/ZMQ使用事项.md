
## 说明
- 多针对于 C++

## 对数据的封装
- zmq 提供了 `message_t` 类进行数据封装，构造函数有多个，常用的为指定数据指针及数据长度的:
  ```c++
    message_t(const void *data_, size_t size_)
  ```

## 接收数据
- 对于本端接收对端发来的一串可打印字符串的代码处理:
  ```c++
    zmq::message_t reply;
    socket.recv(&reply);
    
    printf("%s", (const char *)reply.data());
  ```
  这样的做法是不对的，因为并未指明接收数据的长度是多少。一种正确的做法如下:
  ```c++
    std::string msg((const char*)reply.data(), reply.size());
    printf("%s", msg.c_str());
  ```
  
## send_flags 掩码
```c++
    enum class send_flags : int
    {
        none = 0,
        dontwait = ZMQ_DONTWAIT,
        sndmore = ZMQ_SNDMORE
    };
```


## recv_flags 掩码
```c++
    enum class recv_flags : int
    {
        none = 0,
        dontwait = ZMQ_DONTWAIT
    };
```