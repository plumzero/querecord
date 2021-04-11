
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
