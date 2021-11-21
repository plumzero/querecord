
## 学习参考
- [ZMQ中文指南](https://github.com/anjuke/zguide-cn)
- [ZMQ通信模式:REQ-REP模式](https://www.jianshu.com/p/50bb18c1ab4f)

## ZMQ 安装
- 生成配置文件
  ```shell
    ./autogen.sh
  ```
- 进行配置
  ```shell
    ./configure --prefix=/usr/local/zmq
  ```
- 编译安装
  ```shell
    make
    make install
  ```

## ZMQ 通信模式
- [REQ-REP模式](REQ-REP模式.md)

## ZMQ 使用事项(关于 C++)
- [ZMQ使用事项](ZMQ使用事项.md)

## 测试语言
- C++

## 测试目录说明
- [REQ-REP模式简易示例](1-first/README.md)
- [REQ-REP模式效率测试](2-second/README.md)
