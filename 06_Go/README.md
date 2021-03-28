
## 常量赋值注意
- 常量赋值是一个编译期行为，所以右值不能出现任何需要运行期才能得出结果的表达式，比如试图以
  如下方式定义常量就会导致编译错误:
  ```go
    const Home = os.GetEnv("HOME")
  ```
  上述代码中，os.GetEnv() 只有在运行期才能知道返回结果，在编译期并不确定，所以无法作为常量
  定义的右值。

## 预定义常量
- Go 语言预定义这些常量: true, false 和 iota。
- iota 可以被认为是一个可被编译器修改的常量，在每一个 const 关键字出现时被重置为 0，然后在
  下一个 const 出现之前，每出现一次 iota，其所代表的数字会自动增 1 。
  ```go
    const (             // 遇到 const, iota 被重置为 0
        c0 = iota       // c0 == 0
        c1 = iota       // c1 == 1
        c2 = iota       // c2 == 2
    )
    
    const (
        a = 1 << iota   // a == 1 (遇到 const, iota 被重置为 0)
        b = 1 << iota   // b == 2
        c = 1 << iota   // c == 4
    )
    
    const x = iota      // x == 0
  ```

----

## 枚举
- Go 语言并不支持众多其他语言明确支持的 enum 关键字。
- 可以用 const 后跟一对圆括号的方式定义一组常量，用于表示枚举值:
  ```go
    const (
        Sunday = iota
        Monday
        Tuesday
        Wednesday
        Thursday
        Friday
        Saturday
        numberOfDays
    )
  ```
- 同 Go 语言的其他符号(symbol)一样，以大写字母开头的常量在包外可见。以上例子中 numberOfDays 为
  包内私有，其他符号则可被其他包访问。
  
## 内置类型
- 基础类型
    + 布尔类型: bool
    + 整型: int8 byte int16 int uint uintptr
    + 浮点类型: float32 float64
    + 复数类型: complex64 complex128
    + 字符串: string
    + 字符类型: rune
    + 错误类型: error
- 复合类型
    + 指针 (pointer)
    + 数组 (array)
    + 切片 (slice)
    + 字典 (map)
    + 通道 (chan)
    + 结构体 (struct)
    + 接口 (interface)
- 布尔类型
    + 布尔类型不能接受其他类型的赋值，不支持自动或强制的类型转换。
- 整型
    + int 和 int32 在 Go 语言里被认为是两种不同的类型，编译器不会对这两种类型进行自动转换；
    + 使用强制类型转换可以解决类似于 int 和 int32 之间转换的问题，但要注意精度损失和值溢出问题。
      ```go
        var value2 int32
        value1 := 64        // value1 将被自动推导为 int 类型
        // value2 = value1  // 编译错误
        value2 = int32(value1)
      ```
    + 两个不同的整型数不能直接比较，比如 int8 类型的数和 int 类型的数不能直接比较。但各种类型的
      整型变量都可以直接与字面常量(literal)进行比较，比如:
      ```go
        var i int32
        var j int64
        
        i, j = 1, 2
        
        if i == j {             // 编译错误
            fmt.Println("i and j are equal.")
        }
        
        if i == 1 || j == 2 {   // 编译通过
            fmt.Println("i and j are equal.")
        }
      ```
    + Go 语言中对整型的取反操作是 ^x 。
- 浮点类型
    + Go 语言定义了两种浮点类型, float32 和 float64, 其中 float32 等价于 C 语言的 float 类型，
      float64 等价于 C 语言的 double 类型；
    + 编译器不会对两种浮点类型进行自动转换，可以进行强制类型转换，但要注意安全。
- 复数类型
    + 复数表示
      ```go
        var value1 complex64        // 由 2 个 float32 构成的复数类型
        
        value1 = 3.2 + 12i
        value2 := 3.2 + 12i         // value2 被推导为 complex128 类型
        value3 := complex(3.2, 12)  // value3 结果同 value2
      ```
    + 实部与虚部
      对于一个复数 z = complex(x, y)，可以通过 Go 语言内置函数 real(z)获得该复数的实部，也就是
      x，通过 imag(z)获得该复数的虚部，也就是 y。
- 字符串
    + 字符串的内容可以用类似于数组下标的方式获取，但与数组不同，字符串的内容不能在初始化后被修改:
      ```go
        str := "Hello world"
        ch := str[0]        // 取字符串的第一个字符
        str[0] = 'X'        // 编译错误
      ```
    + 字符串操作
        + 字符串拼接
          ```go
            "Hello" + "123"     // 结果为 Hello123
          ```
        + 计算字符串长度
          ```go
            len("Hello")        // 结果为 5
          ```
        + 取字符
          ```go
            "Hello"[1]          // 结果为 'e'
          ```
    + 字符串遍历
      Go 语言支持两种方式遍历字符串。一种是以字节数组的方式遍历:
      ```go
        str := "Hello world"
        n := len(str)
        for i := 0; i < n; i++ {
            ch := str[i]
            fmt.Println(i, ch)  // ch 的类型是 byte
        }
      ```
      另一种是以 Unicode 方式遍历:
      ```go
        str := "Hello world"
        for i, ch := range str {
            fmt.Println(i, ch)  // ch 的类型是 rune
        }
      ```
- 字符类型
    + Go 语言支持两个字符类型，一个是 byte(实际是 uint8 的别名)，代表 UTF-8 字符串的单个字节的值；
      另一个是 rune, 代表单个 Unicode 字符。
- 数组
    + 元素访问
      Go 语言支持两种元素访问方法。一种和 C 语言相同:
      ```go
        for i := 0; i < len(array); i++ {
            fmt.Println("Element", i , "of array is", array[i])
        }
      ```
      另一种是 range 方式遍历:
      ```go
        for i, v := range array {
            fmt.Println("Array element[", i, "]=", v)
        }
      ```
      range 具有两个返回值，第一个返回值是元素的数组下标，第二个返回值是元素的值。
    + 值类型
      需要注意的是，在 Go 语言中数组是一个值类型(value type)。所有的值类型变量在赋值和作为参数传
      递时都将产生一次复制动作。如果将数组作为函数的参数类型，则在函数调用时该参数将发生数据复制
      。因此，在函数体中无法修改传入的数组的内容，因为函数内操作的只是所传入数组的一个副本。
- 数组切片
    + 原生数组有一些缺点，如数组的长度在定义之后无法再次修改、数组的值类型等，这些会在开发过程中
      造成一些局限。
    + Go 语言提供了数组切片(slice)来弥补数组的不足。从底层实现的角度来看，数组切片实际上仍然使用
      数组来管理元素。同时基于数组，数组切片添加了一系列管理功能，可以随时动态扩充存放空间，并且
      可以被随意传递而不会导致所管理的元素被重复复制。
    + 数组切片的数据结构可以抽象为以下 3 个变量:
        + 一个指向原生数组的指针；
        + 数组切片中的元素个数；
        + 数组切片已分配的存储空间；
    + 创建数组切片
      创建方法主要有两种 —— 基于数组和直接创建。
        + 基于数组
          数组切片可以只使用数组的一部分元素或者整个数组来创建，甚至可以创建一个比所基于的数组还
          要大的数组切片。
          ```go
            package main
            
            import "fmt"
            
            func main() {
                var myArray [10] int = [10] int {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

                // 基于数组创建一个数组切片
                var mySlice [] int = myArray[:5]
                
                fmt.Println("Elements of myArray: ")
                for _, v := range myArray {
                    fmt.Print(v, " ")
                }
                
                fmt.Println("\nElements of mySlice: ")
                
                for _, v := range mySlice {
                    fmt.Print(v, " ")
                }
                
                fmt.Println()
            }
          ```
          基于 myArray 的所有元素创建数组切片:
          ```go
            mySlice = myArray[:]
          ```
          基于 myArray 的前 5 个元素创建数组切片:
          ```go
            mySlice = myArray[:5]
          ```
          基于从第 5 个元素开始的所有元素创建数组切片:
          ```go
            mySlice = myArray[5:]
          ```
        + 直接创建
          Go 语言提供的内置函数 make() 可以用于灵活地创建数组切片。
          创建一个初始元素个数为 5 的数组切片，元素初始值为 0:
          ```go
            mySlice1 := make([]int, 5)
          ```
          创建一个初始元素个数为 5 的数组切片，元素初始值为 0，并预留 10 个元素的存储空间:
          ```go
            mySlice2 := make([]int, 5, 10)
          ```
          直接创建并初始化包含 5 个元素的数组切片:
          ```go
            mySlice3 := []int{1, 2, 3, 4, 5}
          ```
    + 元素遍历
      操作数组元素的所有方法都适用于数组切片。
    + 存储能力
      与数组相比，数组切片多了一个存储能力(capacity)的概念，即元素个数和分配的空间可以是两
      个不同的值。合理设置存储能力的值，可以提高程序性能。
      数组切片支持 Go 语言内置的 cap() 函数和 len() 函数。前者返回的是数组切片分配的空间大
      小，后者返回的是数组切片中当前所存储的元素个数。
      ```go
        package main
        
        import "fmt"
        
        func main() {
            mySlice := make([]int, 5, 10)
            
            fmt.Println("len(mySlice):", len(mySlice))
            fmt.Println("cap(mySlice):", cap(mySlice))
        }
      ```
      程序输出结果为:
      ```go
        len(mySlice): 5
        cap(mySlice): 10
      ```
    + 动态增加元素
      使用 append() 函数，向数组切片中新增元素。
      ```go
        mySlice = append(mySlice, 1, 2, 3)
      ```
      将一个数组切片追加到另一个数组切片的末尾:
      ```go
        mySlice2 := []int{8, 9, 10}
        mySlice = append(mySlice, mySlice2...)
      ```
    + 基于数组切片创建数组切片
      ```go
        oldSlice := []int{1, 2, 3, 4, 5}
        newSlice := oldSlice[:3]    // 基于 oldSlice 的前 3 个元素构建新数组切片
      ```
    + 内容复制
      数组切片支持 Go 语言的另一个内置函数 copy()，用于将内容从一个数组切片复制到另一个数组
      切片。如果加入的两个数组切片不一样大，就会按其中较小的那个数组切片的元素个数进行复制。
      ```go
        slice1 := []int{1, 2, 3, 4, 5}
        slice2 := []int{5, 4, 3}
        
        copy(slice2, slice1)    // 只会复制 slice1 的前 3 个元素到 slice2 中 
        copy(slice1, slice2)    // 只会复制 slice2 的 3 个元素到 slice1 的前 3 个位置
      ```
- 字典
  ```go
    package main
    import "fmt"

    type PersonInfo struct {
        ID string
        Name string
        Address string
    }

    func main() {
        var personDB map[string] PersonInfo
        personDB = make(map[string] PersonInfo)
        
        personDB["12345"] = PersonInfo{"12345", "Tom", "Room 203,..."}
        personDB["1"] = PersonInfo{"1", "Jack", "Room 101,..."}
        
        person, ok := personDB["12345"]
        if ok {
            fmt.Println("Found person", person.Name, "with ID 12345.")
        } else {
            fmt.Println("Did not find person with ID 1234.")
        }
    }
  ```
  上述代码基本上覆盖了 map 的主要用法。这里对一些关键点进行说明:
    + 变量声明
      ```go
        var myMap map[string] PersonInfo
      ```
      其中，myMap 是声明的 map 变量名， string 是键的类型， PersonInfo 则是其中所存放的值类型。
    + 创建
      可以使用 Go 语言内置的函数 make() 来创建一个新 map:
      ```go
        myMap = make(map[string] PersonInfo)
      ```
      也可以选择是否在创建时指定该 map 的初始存储能力:
      ```go
        myMap = make(map[string] PersonInfo, 100)
      ```
      在创建 map 时进行初始化:
      ```go
        myMap = map[string] PersonInfo {
            "1234" : PersonInfo {"1", "Jack", "Room 101,..."},
        }
      ```
    + 元素赋值
      ```go
        myMap["1234"] = PersonInfo{"1", "Jack", "Room 101,..."}
      ```
    + 元素删除
      Go 语言提供了一个内置函数 delect()，用于删除 map 内的元素
      ```go
        delete(myMap, "1234")
      ```
      上述代码表示从 myMap 中删除键为 "1234" 的键值对。
    + 元素查找
      ```go
        value, ok := myMap["1234"]
        if ok {     // 找到了
            // ...
        }
      ```
      判断是否成功找到特定的键，不需要检查取到的值是否是 nil，只需要看第二个返回值 ok 。

## 不定参数
- 不定参数类型
  不定参数是指函数传入的参数个数为不定数量。函数可以进行如下定义以接受不定参数类型:
  ```go
    func myfunc(args ...int) {
        for _, arg := range args {
            fmt.Println(arg)
        }
    }
  ```
  这段代码的意思是，函数 myfunc() 接受不定数量的参数，这些参数的类型全部是 int，它可以用
  如下方式调用:
  ```go
    myfunc(1, 2, 3)
    myfunc(1, 3, 7, 13)
  ```
  形如 ...type 格式的类型只能作为函数的参数类型存在，并且必须是最后一个参数。
- 不定参数的传递
  假设有另一个变参函数叫做 myfunc3(args ...int) ,可以通过如下方式传递变参:
  ```go
    func myfunc(args ...int) {
        // 按原样传递
        myfunc3(args...)
        // 传递片段，实际上任意的 int slice 都可以传进去
        myfunc3(args[1:]...)
    }
  ```
- 任意类型的不定参数
  如果希望传任意类型，可以指定类型为 interface{}。
  以 Go 语言标准库中 fmt.Printf() 的函数原型作为参考示例:
  ```go
    func Printf(format string, args ...interface{}) {
        // ...
    }
  ```
  用 interface() 传递任意类型数据是 Go 语言的惯例用法。
  ```go
    package main

    import "fmt"

    func MyPrintf(args ...interface{}) {
        for _, arg := range args {
            switch arg. (type) {
                case int:
                    fmt.Println(arg, "is an int value.")
                case string:
                    fmt.Println(arg, "is a string value.")
                case int64:
                    fmt.Println(arg, "is an int64 value.")
                default:
                    fmt.Println(arg, "is an unknown type.")
            }
        }
    }

    func main() {
        var v1 int = 1
        var v2 int64 = 234
        var v3 string = "hello"
        var v4 float32 = 1.234
        MyPrintf(v1, v2, v3, v4)
    }
  ```
  
----
  
## 匿名函数与闭包
- 匿名函数
  匿名函数是指不需要定义函数名的一种函数实现方式。
  匿名函数由一个不带函数名的函数声明和函数体组成，如下:
  ```go
    func(a, b int, z float64) bool {
        return a * b < int(z)
    }
  ```
  匿名函数可以直接赋值给一个变量或者直接执行:
  ```go
    f := func(x, y int) int {
        return x + y
    }
    
    func(ch chan int) {
        ch <- ACK
    } (reply_chan)  // 花括号后直接跟参数列表表示函数调用
  ```
- 闭包
    + 闭包是可以包含自由变量的代码块，这些变量不在这个代码块内或者任何全局上下文中定义，而是
      在定义代码块的环境中定义。要执行的代码块为自由变量提供绑定的计算环境(作用域)。
    + 闭包可以作为函数对象或者匿名函数使用。
    + Go 语言中的闭包可以引用函数外的变量。
      ```go
        package main

        import (
            "fmt"
        )

        func main() {
            var j int = 5
            
            a := func() (func()) {
                var i int = 10
                return func() {
                    fmt.Printf("i, j: %d, %d\n", i, j);
                }
            }()
            
            a()
            
            j *= 2
            
            a()
        }
      ```
      执行结果如下:
      ```go
        i, j: 10, 5
        i, j: 10, 10
      ```

----
      
## 错误处理
- error 接口
  Go 语言引入了一个关于错误处理的标准模式，即 error 接口，该接口的定义如下:
  ```go
    type error interface {
        Error() string
    }
  ```
  对于大多数函数，如果要返回错误，大致上都可以定义为如下模式，将 error 作为多种返回值中的最后
  一个，但这并非强制要求:
  ```go
    func Foo(param int)(n int, err Error) {
        // ...
    }
  ```
  调用时的代码建议按如下方式处理错误情况:
  ```go
    n, err := Foo(0)
    
    if err != nil {
        // 错误处理
    } else {
        // 使用返回值n
    }
  ```
  