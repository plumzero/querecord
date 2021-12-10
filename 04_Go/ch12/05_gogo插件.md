
protobuf 会默认会生成一些 tag，如 "json" 等，但如何指定生成某些 tag 呢？ gogoprotobuf 来帮助。

以下面的消息结构为例:
```s
    message Student {
        string stu_name = 1;
        int32 stu_age = 2;
        string address = 3;
    }
```

这里想要指定一个名字为 "bson" 的 tag, 可以这样来定义，并使用 gogoprotobuf 来解析:
```s
    message Student {
        string stu_name = 1 [(gogoproto.moretags) = "bson:\"StuName\""];
        int32 stu_age = 2 [(gogoproto.moretags) = "bson:\"StuAge\""];
        string address = 3 [(gogoproto.moretags) = "bson:\"Address\""];
        ClassName cn = 4 [(gogoproto.jsontag) = "CN"];
    }
```
另外，它的 jsontag 可以重写 protobuf 的 json 标签。

如何获取这个插件呢? 和 `protoc-gen-go` 插件获取方法类似。
- 下载依赖包
  ```sh
    go get -u github.com/gogo/protobuf@v1.3.2
  ```
- 进入指定目录下
  ```sh
    cd $(go env GOPATH)/pkg/mod
    cd github.com/gogo/protobuf@v1.3.2
    cd protoc-gen-gogo
  ```
- 在该目录下编译产生可执行文件
  ```sh
    go build
  ```
  顺利的话可以看到生成一个名称为 `protoc-gen-gogo` 的可执行文件，该文件即为插件。

如何使用呢?
- 按指定结构架设一些文件，主要是 `gogoproto/gogo.proto`
- 进入[这个目录](t5)下，执行如下命令:
  ```sh
    protoc --plugin=protoc-gen-gogo=/path/to/protoc-gen-gogo --gogo_out=plugins=grpc:. *.proto
  ```
  