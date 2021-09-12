
字典序比较，返回值同 clang 的 strcmp 函数。
```go
    func Compare(a, b string) int
```
[Compare程序示例](13/Compare.go)


包含
```go
    func Contains(s, substr string) bool
```

包含任意
```go
    func ContainsAny(s, chars string) bool
```

[Contains和ContainsAny程序示例](13/Contains.go)

统计字符串中的子串个数。
```go
    func Count(s, substr string) int
```
如果 substr 为空，则返回 len(s) + 1 。

[Count程序示例](13/Count.go)

字符串从空白处裂开成字符数组:
```go
    func Fields(s string) []string
```

字符串根据条件裂开成字符数组:
```go
    func FieldsFunc(s string, f func(rune) bool) []string
```

[Fields和FieldsFunc程序示例](13/Fields.go)

字符数组组合成字符串:
```go
    func Join(elems []string, sep string) string
```

[Join程序示例](13/Join.go)

子串 sep 在字符串 s 中第一次出现的位置，不存在则返回 -1
```go
    func Index(s, sep string) int
```

[Index程序示例](13/Index.go)

返回 count 个 s 串联的字符串
```go
    func Repeat(s string, count int) string
```

[Repeat程序示例](13/Repeat.go)

返回将 s 中前 n 个不重叠 old 子串都替换为 new 的新字符串，如果 n < 0 则替换所有 old 子串。
```go
    func Replace(s, old, new string, n int) string
```

[Replace程序示例](13/Replace.go)

分割
```go
    func Split(s, sep string) []string
```

[Split程序示例](13/Split.go)

返回首次出现 c 的索引，如果没有返回 -1。
```go
    func IndexByte(s string, c byte) int
```

[IndexByte程序示例](13/IndexByte.go)

```go
    func IndexRune(s string, r rune) int
```

[IndexRune程序示例](13/IndexRune.go)



基于 Go 语言的值语义特性考量，并且考虑到 Go 的 string 静态特性(一旦初始化就不可被改变)，所以使用 string 进行操作时总会伴随着大量的拷贝，但很多情况下这种操作是没有必要的，这时可以考虑使用 bytes 。

bytes 提供了很多和 strings 相同的操作。

[通过bytes.Buffer更高效地实现字符串连接](13/buffer_join.go)
