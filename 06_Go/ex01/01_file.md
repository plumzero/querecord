
Go 提供了平台无关的，形式风格类 Unix, 错误处理类 Go 的文件操作接口。

这里只对常用的几种进行简单使用说明。

Package: os, io

### Create

创建文件，如果文件已存在则进行截取。

```go
    file, err := os.Create("filefortest.txt")
    if err != nil {
        Log.Fatal(err)
    }
```


### Open

读打开。要求该文件必须存在。
```go
    func Open(name string) (*File, error)
```

模式打开
```go
    func OpenFile(name string, flag int, perm FileMode) (*File, error)
```


### Write

字节流写入
```go
    func (f * File) Write(b []byte) (n int, err error)
```
向 File 中写入 b 个字节。n 记录实际写入的字节数。

字符串写入
```go
    func (f * File) WriteString(s string) (n int, err error)
```


### Read

```go
    func (f * File) Read(b []byte) (n int, err error)
```
n 表示实际读取的字节数。

偏移读:
```go
    func (f * File) ReadAt(b []byte, off int64) (n int, err error)
```


### Seek

设置文件偏移:
```go
    func (f * File) Seek(offset int64, whence int) (ret int64, err error)
```
whence 的可取值有: `io.SeekStart`, `io.SeekCurrent`, `io.SeekEnd` 。


### Close

关闭文件
```
    func (f * File) Close() error
```

[创建测试](01/Create.go)

[读测试](01/Read.go)

[写测试](01/Write.go)

[偏移测试](01/Seek.go)
