
`GOPATH` 环境变量列出了 Go 代码的搜索路径，可以通过命令 `go env GOPATH` 查看当前值。

GOPATH 下的路径都有规定的结构，称为标准布局:
* `src` 是源码目录，src 目录下的路径决定了要引入的路径(import path)以及可执行程序。假如 DIR 是 GOPATH 中的一个目录路径，那么绝对路径为 `DIR/src/foo/bar` 的包可以像这样引入到其他文件:`foo/bar`。
* `pkg` 是包安装目录。
* `bin` 用于存放编译好的命令。比如在`DIR/src/foo/quux`下生成的命令将被安装到`DIR/bin/quux`中。

当 `GOPATH=/home/user/go` 时，示例布局如下:
```shell
    /home/user/go/
        src/
            foo/
                bar/               (go code in package bar)
                    x.go
                quux/              (go code in package main)
                    y.go
        bin/
            quux                   (installed command)
        pkg/
            linux_amd64/
                foo/
                    bar.a          (installed package object)
```

GOPATH 可能包含有多个路径，Go 会搜索每个路径去寻找相应的源码文件。不过，当需要下载第三方的包时，只会将其下载到 GOPATH 路径列表的第一个路径中，这是需要注意的地方。


### GOPATH 和 Modules

使用模块时，GOPATH 是无意义的，不过它还是会把下载的依赖储存在 $GOPATH/pkg/mod 中。

### 内部目录

如下布局:
```shell
    /home/user/go/
        src/
            crash/
                bang/              (go code in package bang)
                    b.go
            foo/                   (go code in package foo)
                f.go
                bar/               (go code in package bar)
                    x.go
                internal/
                    baz/           (go code in package baz)
                        z.go
                quux/              (go code in package main)
                    y.go
```
对于上面的 `internal` 目录，如果想要使用 z.go 文件中的代码，可以通过引入`foo/internal/baz`路径，但只限于 foo 目录。也就是说`foo/f.go`、`foo/bar/x.go`、`foo/quux/y.go` 都可以引入`foo/internal/baz`路径，但是`crash/bang/b.go`却不可以。


### Vendor 目录(Vendor Diectories)

从 Go 1.6 开始，通过 vendoring 使项目实现对外部依赖的引入。

如下布局:
```shell
    /home/user/go/
        src/
            crash/
                bang/              (go code in package bang)
                    b.go
            foo/                   (go code in package foo)
                f.go
                bar/               (go code in package bar)
                    x.go
                vendor/
                    baz/           (go code in package baz)
                        z.go
                quux/              (go code in package main)
                    y.go
```
与 internal 的布局是相同的，但它以 `vendor` 作为"根"。假如要使用 z.go 的代码，只需要引入 `baz` 而不是 "foo/vendor/baz"，vendor 目录下的源码树会屏蔽更高层级目录下的源码树。在 `foo` 作为"根"目录下的文件，比如说 `foo/bar/x.go` 在引入 `crash/bang` 时，将会被解析为 `foo/vendor/crash/bang`，但显然 vendor 中并不存在相关的文件。

`go get` 无法检出或更新 vendor 目录下的代码。
