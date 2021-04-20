
进行 grpc 编程时，
```shell
    go get github.com/golang/protobuf
```


### 根据 .proto 生成相应 .go 文件

[.proto 文件](t2/msgdata.proto)

执行如下命令生成 .go 文件:
```shell
    protoc --go_out=. *.proto
```

### 引入 go mod 进行包管理

进入这个[路径](t2)下执行如下命令，生成 `go.mod` 文件:
```shell
    go mod init ipc.com
```

### 创建服务端与客户端入口文件

根据上面创建的包管理，创建[服务端](t2/server.go)和[客户端](t2/client.go)文件。

在一个 shell 会话中开启服务端:
```shell
    go run server.go
```

在另一个 shell 会话中开启客户端:
```shell
    go run client.go
```

依次在客户端一侧输入如下内容，观察服务端响应:
```shell
    hello world
    stop
```
