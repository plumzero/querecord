
反射机制就是在运行时动态调用对象的方法和属性，标准库的 reflect 包提供了相关的功能。在 reflect 包中，通过 `reflect.TypeOf()` 和 `reflect.ValueOf()` 分别从类型、值的角度来描述一个 Go 对象。
```go
    func TypeOf(i interface{}) Type
    type Type interface

    func ValueOf(i interface{}) Value
    type Value struct
```
`reflect.Type` 和 `reflect.Value` 是 Go reflect 包中最重要的两个类型。Type 主要表达的是被反射的这个变量本身的类型信息，而 Value 则为该变量实例本身的信息。通过函数 `reflect.TypeOf()` 和 `reflect.ValueOf()` 分别返回被检查对象的类型和值。

reflect.Type 和 reflect.Value 还有许多其他检查和操作方法。

关于 reflect.Type 的主要方法有:
* `Kind()` 返回一个常量，表示具体类型的底层类型。
* `Elem()` 返回指针、数组、切片、字典、通道等类型。这个方法要慎用，如果用于其他类型会出现运行时异常。

关于 reflect.Value 的主要方法有:
* `Kind()` 返回一个常量，表示具体类型的底层类型。
* `Type()` 返回具体类型所对应的 reflect.Type(静态类型)。

反射让我们可以在程序运行时动态检查类型和变量，例如它的值、方法和类型，甚至可以在运行时修改和创建变量、函数和结构。

不过反射虽然强大，但对性能有一定的影响，因此除非必要，应当避免使用或小心使用。

[类型反射测试](01/type_reflect.go)


### 通过反射修改对象

通过反射可以修改对象，但对象必须是可寻址的。简单来说，如果想通过反射修改对象，就需要把想修改对象的指针传递过来。如果对象不能被寻址，就是不可写(不可修改)的。所以通过反射修改原对象，需要判断其可写性，也就是可寻址。

实际上，要修改的是指针指向的数据，需要调用 Value 类型的 `Elem()` 方法。Elem() 方法能够对指针进行间接引用，将结果存储到 reflect.Value 类型对象中。
```go
    v := reflect.Value.Elem()
```
通过 `CanSet()` 方法来判断原始反射对象 v 是否可写，通过 `CanAddr()` 方法可以判断它是否可被取地址。函数签名如下:
```go
    func (v Value) CanAddr()
    func (v Value) CanSet() bool
```

要通过反射方式修改对象，重点是通过方法 Elem() 获取原始值对应的反射对象。虽然反射可以越过 Go 语言导出规则的限制读取结构体中不可导出的成员，但不能修改它们。只有可导出的字段才是可写的。
```go
    type Student struct {
        name string         // 不可导出，不可写
        Age int             // 可导出，可写
    }
```

[修改对象](01/settable.go)

如果在结构体中有 `tag` 标签，通过反射可获取结构体成员变量的 tag 信息。

[获取tag信息](01/tag.go)


### 通过反射创建基础类型和用户自定义类型变量

除了可以通过反射创建基础类型和用户自定义类型，还可以使用反射创建切片、字典、通道，甚至包括函数类型。常见函数有: `reflect.Makeslice()`、`reflect.MakeMap()`、`reflect.MakeChan()`。

要想创建变量，需要先确定类型。一般的步骤是:
* 根据 reflect.Type(t) 得到 t 的静态类型
* 接着使用 `reflect.New(vartype)` 生成新变量
* 之后新变量通过方法 Elem() 获取的反射对象来设置变量值
* 最后可以使用 Elem().interface() 来反引用 reflect 的指针，得到新变量的值

[创建变量](01/new.go)

通过反射机制，能对一个结构体类型的大致结构如方法、字段的情况有较为全面的了解。

[结构体类型测试](01/reflect_struct.go)
