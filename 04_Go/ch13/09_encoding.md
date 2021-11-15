
### Base64

Base64 是网络上最常见的用于传输 8 位字节流的编码方式之一，可用于在 HTTP 环境下传递较长的标识信息。

Go 的 encoding/base64 提供了对 Base64 的编/解码操作。

encoding/base64 定义了一个 Encoding 结构体，表示 Base64 的编/解码器，并且导出了四个常用的 Encoding 对象: `StdEncoding`, `URLEncoding`, `RawStdEncoding`, `RawURLEncoding` 。
* StdEncoding 表示标准的编/解码器。
* URLEncoding 用于对 URL 编/解码，编/解码过程中会将 Base64 编码中的特殊标记 "+" 和 "/" 替换为 "-" 和 "_"。
* RawStdEncoding 和 RawURLEncoding 分别是上述两者的非 padding 版本。

[程序示例](09/b64.go)


### Hex


Go 语言内建了 hex 标准库用于十六进制编码解码工作的标准包。

常用函数有 `hex.Encode` 和 `hex.Decode`。两个函数都接受两个 byte 数组作为参数: 一个作为数据源，一个作为输出源，且输出源的长度一般是数据源长度的 2 倍。

[程序示例](09/hex.go)


### Json

Go 语言内置 encoding/json 标准库，开发者可以轻松使用 Go 程序生成和解析 JSON 格式的数据。

Go 语言实现的对 JSON 的编码和解码，遵循 RFC4627 协议标准。

1. JSON 编码

使用如下函数进行 JSON 编码:
```go
    func Marshal(v interface{}) ([]byte, error)
```

Go 语言的大多数数据类型都可以转化为有效的 JSON 文本，但 channel, complex 和函数这几种类型除外。

如果JSON要编码的数据结构中出现指针，那么将会对指针所指向的值进行编码，如果指针指向的是 nil，那么 null 将作为编码后的结果输出。

在 Go 中，Json 编码前后的数据类型映射如下:
- 布尔值编码为 JSON 后还是布尔类型
- 浮点数和整型会被编码为 JSON 里边的常规数字
- 字符串将以 UTF-8 形式编码为 Unicode 字符集的字符串，特殊字符比如 `<` 将会被编码为 `\u003c`
- 数组和切片会编码为 JSON 里边的数组，但 []byte 类型的值将会编码为 Base64 形式的字符串，slice 类型的零值会被编码为 null
- 结构体会转化为 JSON 对象，并且只有结构体里边以大写字母开头的可被导出的字段才会被转化输出，而这些可导出的字段会作为 JSON 对象的字符串索引
- 编码一个 map 类型的数据结构时，该数据的类型必须是 map[string]T 形式，其中 T 可以是 encoding/json 包支持的任意数据类型

[编码示例](09/json_Marshal.go)


2. JSON 解码

使用如下函数进行 JSON 解码:
```go
    func Unmarshal(data []byte, v interface{}) error
```
该函数的第一个参数是输入，即 JSON 格式的文本，第二个参数表示目标输出容器。


3. 解码未知结构的 JSON 数据

如果要解码一段未知结构的 JSON，只需将这段 JSON 数据解码输出到一个空接口即可。在解码 JSON 数据的过程中，JSON数据里边的元素类型将做如下转换:
- JSON 中的布尔值将会解码为 Go 中的 bool 类型
- 数值会被解码为 float64 类型
- 字符串被解码为 string 类型
- JSON数组被解码为 []interface{} 类型
- JSON对象被解码为 map[string]interface{} 类型
- null 被解码为 nil

[解码未知结构JSON数据示例](09/json_UnmarshalUnknown.go)


4. JSON 的流式读写

Go encoding/json 包还提供 Decoder 和 Encoder 两个类型，用于支持 JSON 数据的流式读写，并提供 NewDecoder() 和 NewEncoder() 两个函数来进行具体实现:
```go
    func NewDecoder(r io.Reader) *Decoder
    func NewEncoder(w io.Writer) *Encoder
```

[流式读写示例](09/json_streamIO.go)

[将JSON数据映射到结构体](09/json_struct.go)

### CSV

[读csv测试](09/csv_reader.go)
