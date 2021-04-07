
工程目录组织形式如下:
```sh
    ├── bin
    ├── pkg
    └── src
        ├── cg
        │   ├── centerclient.go
        │   ├── center.go
        │   └── player.go
        ├── cgss
        │   └── cgss.go
        └── ipc
            ├── client.go
            ├── ipc_test.go
            └── server.go
```
其中 `cgss.go` 是主程序。

测试
```shell
    go test ipc
```

设置 GOPATH 路径，并运行工程
```shell
    export GOPATH=$GOPATH:/path/to/gameserver
```

运行
```shell
    # go run cgss
    Casual Game Server Solution
    A new session has been created successfully.

                    Commands:
                            login <username><level><exp>
                            logout <username>
                            send <message>
                            listplayer
                            quit(q)
                            help(h)

    Command> login Tom 1 101
    Command> login Jerry 2 321
    Command> listplayer
    1 : &{Tom 1 101 <nil>}
    2 : &{Jerry 2 321 <nil>}
    Command> send Hello everybody.
    Tom received message: Hello everybody.
    Jerry received message: Hello everybody.
    logout Tom
    Command> listplayer
    1 : &{Jerry 2 321 <nil>}
    Command> logout p^H
    Command> logout Jerry
    Command> listplayer
    Failed. No player online.
    Command> q
```
