
执行编译的时候出现了下面的错误:
```s
CMakeFiles/program.dir/__/realize/source.cc.o: In function `proto_to_csv[abi:cxx11](google::protobuf::Message const&, bool)':
/home/fangyi/gitlab/project/src/module/hello/realize/internal_util.h:14: multiple definition of `proto_to_csv[abi:cxx11](google::protobuf::Message const&, bool)'
CMakeFiles/program.dir/program.cpp.o:/home/fangyi/gitlab/project/src/module/hello/realize/internal_util.h:14: first defined here
```

看了一下， proto_to_csv 这个函数是定义在了 .h 为后缀的头文件中，如下:
```cpp
    const std::string proto_to_csv(const google::protobuf::Message& msg, bool is_header) {
        ...
    }
```
这个头文件在 main 函数文件和另一个 .cpp 文件中各引用了一次。

对于上面的错误，其中的一个解决办法是将函数声明和实现分开，即在 .h 文件中进行声明，而在 .cpp 文件中实现。其他文件在使用这个函数时，只需要引用相应的头文件即可。

不过那样太麻烦了，有一种简单的办法是通过 `inline` 关键字进行修饰。如下:
```cpp
    inline const std::string proto_to_csv(const google::protobuf::Message& msg, bool is_header) {
        ...
    }
```
这样就可以编译通过了。
