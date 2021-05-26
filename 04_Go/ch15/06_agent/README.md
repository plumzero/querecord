
工程目录组织形式如下:
```sh
    ├── bin
    ├── pkg
    ├── README.md
    └── src
        ├── busi
        │   ├── tcb.go
        │   └── tcb_test.go
        └── faci
            ├── agent.go
            └── cells.go
```

设置 GOPATH 路径
```shell
    export GOPATH=/home/github/ldev/04_Go/ch10/06_agent
```

测试
```shell
    go test -v busi
```
