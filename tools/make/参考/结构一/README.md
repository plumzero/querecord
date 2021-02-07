
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
    └─pistache
        ├─include
        └─lib
  ```
- 主目录下包含入口文件，asn1c 目录下为源文件，curl 和 pistache 为依赖的静态库及相关头文件。