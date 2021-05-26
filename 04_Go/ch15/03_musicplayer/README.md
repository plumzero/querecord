
工程目录组织形式如下:
```sh
    ├── bin
    ├── pkg
    └── src
        ├── mlib
        │   ├── manager.go
        │   └── manager_test.go
        ├── mp
        │   ├── mp3.go
        │   ├── play.go
        │   └── wav.go
        └── mplayer
            └── mplayer.go
```
其中 `mplayer.go` 是主程序。

设置 GOPATH 路径
```shell
    export GOPATH=$GOPATH:/path/to/musicplayer
```

测试
```shell
    go test -v mlib
```

运行
```shell
    # go run mplayer

                            Enter following commands to control the player:
                            list list -- View the existing music lib
                            list add <name><artist><source><type> -- Add a music to the music lib
                            lib remove <name> -- Remove the specified music from the lib
                            play <name> -- Play the specified music

    Enter command-> lib add HugeStone MJ ~/MusicLib/hs.p3 MP3
    Enter command-> play HugeStone
    Playing MP3 music ~/MusicLib/hs.p3
    ..........
    Finished playing ~/MusicLib/hs.p3
    Enter command-> lib list
    1 : HugeStone MJ ~/MusicLib/hs.p3 MP3
    Enter command-> q
```
