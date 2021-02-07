
### Reference

[CMake 入门实战](https://www.hahack.com/codes/cmake/)

[cmake-commands(7)](https://cmake.org/cmake/help/v3.4/manual/cmake-commands.7.html)

更多参考来自于开源项目，如 mbedtls, curl, restbed 等。


### Contents

1. [语法变量](语法变量.md)
2. [常用指令](常用指令.md)
3. [使用示例](使用示例.md)
4. [实用技巧](实用技巧.md)
5. [使用注意](使用注意.md)


### Other Useage

1. [find_package的使用](find_package的使用/)
2. [通过cmake向源文件中传入宏](通过cmake向源文件中传入宏/)


### Suggestion

- 如果工程只有几个文件，直接编写 Makefile 是最好的选择；
- 如果使用的是 C/C++/Java 之外的语言，请不要使用 cmake(至少目前是这样)；
- 采用外部构建方式(out-of-source)，这样所有的动作发生在编译目录，对原有工程没有任何影响；
- 选择更优良的构建体系，不要为了使用 cmake 而使用 cmake；


### Attention

- cmake 生成的 Makefile 不支持 make distclean;
- cmake 中通过 ${} 来引用变量，但在 IF 控制语句中，变量直接使用变量名引用，而不需要 ${};
- 生成 Makefile 文件，使用 make 编译时通过指定 VERBOSE=1 可以进行详细的编译输出。