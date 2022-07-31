
检测端口服务是否连通 telnet

开启一个网络服务时，需要将对应此服务的端口开放，供客户端连接。

客户端可以通过 telnet 命令测试对端连通性
```shell
    telnet 192.168.0.105 peer_port
```
如果出现如下打印说明端口连通
```shell
    Trying 192.168.0.105...
    Connected to 192.168.0.105.
    Escape character is '^]'.
```

如果出现如下打印说明端口未连通
```shell
    Trying 192.168.0.105...
    telnet: Unable to connect to remote host: No route to host
```

服务其实就是端口的子集，所以也可以通过 curl 或 wget 命令测试端口的连通性。
