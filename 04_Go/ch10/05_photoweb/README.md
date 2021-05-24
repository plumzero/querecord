
工程目录组织形式如下:
```sh
    ├── photoweb.go
    ├── public
    │   ├── css
    │   ├── images
    │   └── js
    ├── uploads
    └── views
        ├── list.html
        └── upload.html
```
其中 `photoweb.go` 是主程序，也是唯一的一个程序。

运行
```shell
    # go run photoweb.go
```

在浏览器上访问 `ip:8080/upload`，执行相关操作。
