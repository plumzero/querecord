
valarray 类模板定义了保存和操作数值序列的对象的类型，主要用来处理整数和浮点数。


### valarray 对象的基本操作

[valarray构造示例](03_valarray/01_construct.cpp)

valarray 对象和 array 容器一样，不能添加或删除元素。但是能够通过成员函数 resize() 改变 valarray 容器中的元素个数，为其赋新值。

成员函数 swap() 可以交换当前对象和作为参数传入的另一个同类型 valarray 对象的元素。

成员函数 min() 和 max() 可以用来查找元素的最小值和最大值。

成员函数  sum() 会返回元素的和。

valarray 没有返回元素迭代器的成员函数，但可以通过全局 begin() 和 end() 返回随机访问迭代器。

成员函数 shift() 会将全部的元素序列移动由参数指定的位数。函数会返回一个新的 valarray 对象作为结果，原序列不变。

成员函数 cshift() 会将元素序列循环移动由参数指定的数目的位置。它是会返回一个新的对象。

成员函数 apply() 可以将一个函数应用到每一个元素上，并返回一个新的 valarray 对象作为结果。它定义了两个重载:
```c++
    valarray<T> apply(T func(T)) const;
    valarray<T> apply(T func(const T&)) const;
```
无论哪一种重载，均不能修改原始元素。

valarray 定义了许多来自于 cmath 头文件的函数重载版本。这里接受一个 valarray 对象为参数和函数有:
```sh
    abs(), pow(), sqrt(), exp(), log(), log10(), sin(), cos(), tan(), asin(),
    acos(), atan(), atan2(), sinh(), cosh(), tanh()
```

[基本操作示例](03_valarray/02_base_operation.cpp)


### 一元运算符

有 4 个可以应用到 valarray 对象的一元运算符: `+` `-` `~` `!` 。效果是将运算符应用到数组的每个元素上，并返回一个新的 valarray 对象作为结果，不改变原对象。

`!` 运算符得到的新元素总为布尔类型，所以这个运算的结果是一个 valarray<bool> 类型的对象。

`~` 运算符是位的 NOT(位的取反)或 1 的补码。

`+`运算符对数值没有效果，`-`运算符会改变符号。 

[一元运算符示例](03_valarray/03_unary_operation.cpp)


### 用于 valarry 对象的复合赋值运算符

所有的复合赋值运算符的左操作数都是 valarray 对象，右操作数是一个和所保存的元素同类型的值。

右操作数也可以是和左操作数有相同元素个数和元素类型的 valarray 对象。

[复合运算符示例](03_valarray/04_composite_operation.cpp)


### valarray 对象的二元运算

在 valarray 头文件中定义了下面这些二元运算符的非成员操作符函数:
- 算术运算符: `+` `-` `*` `/` `%`
- 位操作运算符: `&` `|` `^`
- 位移运算符: `>>` `<<`
- 逻辑运算符: `&&` `||`
- 比较运算符: `==` `!=` `<` `<=` `>` `>=`

这些运算符有不同的版本，可以应用到一个 valarray<T> 对象和一个 T 类型对象上、一个 T 类型对象和一个 valarray<T> 对象上，或者应用到两个 valarray<T> 对象上。应用到两个 valarray<T> 对象上要求它们有相同个数的同类型元素。

逻辑运算符和比较运算符会返回一个和 valarray 操作数相同个数元素的 valarray<bool> 对象。

[二元运算符示例](03_valarray/05_binary_operation.cpp)


### 访问 valarray 对象中的元素

valarray 对象以序列方式保存元素，可以通过下标运算符索引得到任何元素的引用。

[索引访问示例](03_valarray/06_access.cpp)


### 切片

std::slice 对象可以作为索引传递给 valarray 对象的下标运算符，由此可以从 valarray 对象中来选择两个或多个元素。

通过 slice 选择的数组元素可以作为引用，因此可以访问或改变这些元素的值。

构造 slice 对象需要三个参数，依次是用于指定 valarray 对象中的起始索引、要选择子集的元素个数、步进增量。
```c++
    std::slice s{ 3, 4, 2 };    // start index = 3, size = 4, stride = 2
```
调用 slice 对象的成员函数 start(), size(), stride() 可以分别返回以上三个参数。

[切片示例](03_valarray/07_slice.cpp)

在用 slice 对象作为下标时，slice_array<T> 对象是从 valarray<T> 对象选择的子集的代理。
```c++
    data[std::slice{0, 5, 1}] = 99;
```
在以上代码中，表达式 `data[std::slice{0, 5, 1}]` 在赋值运算符的左边生成 slice_array。这里调用了 slice_array 的成员函数 operator=()。

右操作数可以是一个单值元素，或是一个包含相同类型元素的 valarray，或是另一个同类型的 slice_array。

当右操作数是 valarray 或 slice_array 时，必须保证 它至少包含和左操作数一样多的元素，否则无法得到预期结果。

slice_array 对象适用以下运算符:
- 算术运算符: `+=` `-=` `*=` `/=` `%=`
- 位操作运算符: `&=` `|=` `^=`
- 移位运算符: `>>=` `<<==`

在上面这些运算符中，左操作数必须是一个 slice_array 对象，右操作数都必须是一个包含和 slice_array 同类型元素的 valarray 对象。

[slice_array示例](03_valarray/08_slice_array.cpp)


### 有条件地选择元素

使用 valarray<bool> 对象作为下标的结果是得到一个 mask_array<T> 对象，数组中正在访问的就是 T 类型的值。

[示例](03_valarray/09_mask_array.cpp)
