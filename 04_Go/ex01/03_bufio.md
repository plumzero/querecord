
有缓冲的 I/O 。

### NewReader

创建读缓冲
```go
    func NewReader(rd io.Reader) *Reader
```

创建指定缓冲长度的读缓冲
```go
    func NewReader(rd io.Reader, size int) *Reader
```


### Read

类似 Posix 中的 fread 函数。
```go
    func (b * Reader) Read(p []byte) (n int, err error)
```

单字节获取，类似 Posix 中的 fgetc 函数。
```go
    func (b * Reader) ReadByte() (byte, error)
```

字节扫描段读取
```go
    func (b * Reader) ReadBytes(delim byte) ([]byte, error)
```
直到第一次遇到 delim 字节时读取结束，读取内容包含 delim 字节。

行读取，类似 Posix 中的 getline 函数，但不包含新行符。
```go
    func (b * Reader) ReadLine()(line []byte, isPrefix bool, err error)
```
读取字节数超过缓冲区时，isPrefix 置 true，可以判断此标志以确定是否需要进行继续读取。

字符扫描段读取
```go
    func (b * Reader) ReadString(delim byte) (string, error)
```


### NewWriter

创建写缓冲
```go
    func NewWriter(w io.Writer) *Writer
```

创建指定缓冲长度的写缓冲
```go
    func NewWriterSize(w io.Writer, size int) *Writer
```


### Write

将流刷入 I/O
```go
    func (b * Writer) Flush() error
```

类似于 Posix 中的 fwrite 函数。
```go
    func (b * Writer) Write(p []byte) (nn int, err error)
```

类似于 Posix 中的 fputc 函数。
```go
    func (b * Writer) WriteByte(c byte) error
```

写入字符串
```go
    func (b * Writer) WriteString(s string) (int, error)
```


[写测试](03/WriteBuf.go)

[读测试](03/ReadBuf.go)
