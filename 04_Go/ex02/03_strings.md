
### Compare

字典序比较，返回值同 clang 的 strcmp 函数。
```go
    func Compare(a, b string) int
```

[程序示例](03/Compare.go)


### Contains

包含
```go
    func Contains(s, substr string) bool
```

包含任意
```go
    func ContainsAny(s, chars string) bool
```

[程序示例](03/Contains.go)


### Count

统计字符串中的子串个数。
```go
    func Count(s, substr string) int
```
如果 substr 为空，则返回 len(s) + 1 。

[程序示例](03/Count.go)


### Fields

字符串从空白处裂开成字符数组:
```go
    func Fields(s string) []string
```

字符串根据条件裂开成字符数组:
```go
    func FieldsFunc(s string, f func(rune) bool) []string
```

[程序示例](03/Fields.go)


### Join

字符数组组合成字符串:
```go
    func Join(elems []string, sep string) string
```

[程序示例](03/Join.go)


### Index

子串 sep 在字符串 s 中第一次出现的位置，不存在则返回 -1
```go
    func Index(s, sep string) int
```

[程序示例](03/Index.go)


### Repeat

返回 count 个 s 串联的字符串
```go
    func Repeat(s string, count int) string
```

[程序示例](03/Repeat.go)


### Replace

返回将 s 中前 n 个不重叠 old 子串都替换为 new 的新字符串，如果 n < 0 则替换所有 old 子串。
```go
    func Replace(s, old, new string, n int) string
```

[程序示例](03/Replace.go)


### Split

分割
```go
    func Split(s, sep string) []string
```

[程序示例](03/Split.go)


### IndexByte

返回首次出现 c 的索引，如果没有返回 -1。
```go
    func IndexByte(s string, c byte) int
```

[程序示例](03/IndexByte.go)
