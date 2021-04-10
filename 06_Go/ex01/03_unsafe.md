
Go 是一种强类型语言，编译器会对数据类型进行检查。不同类型的数据不能赋值，并且不支持隐式转换。

但是 Go 提供了 3 种类型转换机制来实现不同类型之间的转换。

### POD类型转换

[示例程序](03/pod_type_switch.go)


### unsafe 实现指针转换

Go 中指针也是有类型的。对于如下代码，会报编译错误:
```go
    var a int32 = 10
    var p *int32 = &a
    var c *int64
    c = (*int64)(p)
}
```
原因是无法实现从 *int32 到 *int64 之间的指针转换。

指针的强制类型转换需要用到 `unsafe` 包中的函数实现。

[指针转换示例](03/unsafe.go)

当然，这种转换是不安全的。

不过，只要对结构体内存有所认识，unsafe 依然够强。证据如下:

[struct转换示例一](03/struct_switch_as_member.go)

[struct转换示例二](03/struct_switch_as_parameter.go)


### 类型断言

略
