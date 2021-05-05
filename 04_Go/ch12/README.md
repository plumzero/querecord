
关于 golang/protobuf 与 protobuffers/protobuf，是利用 `golang/protobuf` 产生 `protoc-gen-go` 插件，通过这个插件去 `protobuffers/protobuf` 生成相关的 .go 文件。

为了保证后续顺利进行，有必要设置一下代理:
```shell
    go env -w GOPROXY=https://goproxy.cn,direct
```
