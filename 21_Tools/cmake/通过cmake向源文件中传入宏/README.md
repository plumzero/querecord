
## 说明
- 为了演示 cmake 参数是可以向子目录中传递的，所以使用了 cmake 目录迭代。

## 操作步骤
- 将 c/c++ 源文件中用到的宏定义到 subdir/config.h.in 中；
- 在 subdir/CMakeLists.txt 设置上述 .in 文件中用到的宏的缺省值；
- 在源文件中添加 config.h 头文件，并加入编译时搜索路径；
- 通过 cmake 命令选项指定宏值
  ```cmake
    cmake . -DCONF_PATH=./path/to/new.conf -DVERSION_MAJOR=2
  ```