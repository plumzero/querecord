
## 说明
- 文件结构
  ```shell
    │  makefile
    │
    ├─asn1c
    │      makefile
    │
    ├─curl
    │  ├─include
    │  └─lib
    ├─doctest
    ├─pistache
    │  ├─include
    │  └─lib
    └─utest
            makefile
  ```
- asn1c 目录下为源文件，用作生成静态库文件，curl 和 pistache 为依赖的静态库及相关头文件。
- 主目录下的文件与 asn1c curl pistache 一起生成新的静态库文件。
- 新的静态库文件由 utest 调用进行单元测试。
