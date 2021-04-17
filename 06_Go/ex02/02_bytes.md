
基于 Go 语言的值语义特性考量，并且考虑到 Go 的 string 静态特性(一旦初始化就不可被改变)，所以使用 string 进行操作时总会伴随着大量的拷贝，但很多情况下这种操作是没有必要的，这时可以考虑使用 bytes 。

bytes 提供了很多和 strings 相同的操作。

[通过bytes.Buffer更高效地实现字符串连接](02/Buffer_join.go)
