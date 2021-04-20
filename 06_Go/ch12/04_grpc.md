
获取 grpc 支持:
```shell
    go get google.golang.org/grpc
```

### 根据 .proto 生成相应 .go 文件

[.proto 文件](t4/helloworld.proto)

执行如下命令生成 .go 文件:
```shell
    protoc --go_out=plugins=grpc:./ *.proto
```


### 引入 go mod 进行包管理

进入这个[路径](t4)下执行如下命令，生成 `go.mod` 文件:
```shell
    go mod init ipc.com
```
修改 `go.mod` 文件，使用指定版本的 grpc 。修改后的结果如下:
```mod
    module ipc.com

    go 1.13

    require (
        google.golang.org/grpc v1.32.0
    )
```


### 创建服务端与客户端入口文件

根据上面创建的包管理，创建[服务端](t4/grpc_server.go)和[客户端](t4/grpc_client.go)文件。

在一个 shell 会话中开启服务端:
```shell
    go run grpc_server.go
```

在另一个 shell 会话中开启客户端:
```shell
    go run grpc_client.go
```

观察结果。
