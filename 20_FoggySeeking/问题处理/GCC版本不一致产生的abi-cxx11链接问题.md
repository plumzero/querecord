
### 问题描述

在 A 机器上编译生成的 C++ 动态库，拿到 B 机器上使用，产生链接问题。部分报错如下:
```sh
    CMakeFiles/greeter_server.dir/greeter_server.cpp.o: In function `main':
    /home/grpc/mytest/01_first/greeter_server.cpp:50: undefined reference to `grpc::ServerBuilder::AddListeningPort(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::shared_ptr<grpc::ServerCredentials>, int*)'
    CMakeFiles/greeter_server.dir/greeter_server.cpp.o: In function `google::protobuf::internal::GetEmptyStringAlreadyInited[abi:cxx11]()':
```
关键字是 `abi:cxx11`。


### 问题原因

[参考](https://stackoverflow.com/questions/30124264/undefined-reference-to-googleprotobufinternalempty-string-abicxx11)

如果使用 GCC 4.x 或这之前的编译器版本生成动态库，再使用 GCC 5.x 编译应用程序时会产生这个问题。

确认了一下，A 机器 GCC 版本为 4.8.5，B 机器 GCC 版本为 5.4.0 , 描述一致。


### 解决办法

在 B 机器上重新编译库。