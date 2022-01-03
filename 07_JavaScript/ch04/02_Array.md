
ES 数组是一组有序的数据，但跟其他语句不同的是，数组中的每个槽位可以存储任意类型的数据。

ES 数组是动态大小的，会随着数据添加而自动增长。

### 创建数组

一种是使用 Array 构造函数:
```js
    let colors = new Array();
```
如果知道数组中元素的数量，那么也可以给构造函数传入一个数值，然后 length 属性就会被自动创建并设置为这个值:
```js
    let months = new Array(12);
```
也可以给 Array 构造函数传入要保存的元素:
```js
    let triples = new Array("red", "blue", "green");
```
这就需要注意一个问题，因为如果这个值是数值，则会创建一个长度为指定数值的数组；而如果这个值是其他类型的，则会创建一个只包含该特定值的数组。

在使用 Array 构造函数时，也可以省略 new 操作符，结果是一样的。

另一种创建数组的方式是使用数组字面量表示法:
```js
    let colors = ["red", "blue", "green"];  // 创建一个包含 3 个元素的数组
    let names = [];     // 创建一个空数组
```
与对象一样，使用数组字面量表示法创建数组不会调用 Array 构造函数。

ES6 新增了两个用于创建数组的静态方法: from() 和 of()。`from()` 用于将类数组结构(就是任何可迭代的结构)转换为数组实例，`of()` 用于将一组参数转换为数组实例。

[from转数组示例](t/02_array_from.js)

Array.from() 还接收第二个可选的映射函数参数。这个函数可以直接增强新数组的值，而无须像调用 Array.from().map() 那样先创建一个中间数组:
```js
    const old_array = [1, 2, 3, 4];
    const new_array = Array.from(old_array, x => x**2);
    console.log(old_array);
    console.log(new_array);
```

还可以接收第三个可选参数，用于指定映射函数中 this 的值:
```js
    const a1 = [1, 2, 3, 4];
    const a = Array.from(a1, function(x) { return x**this.exponent }, {exponent: 3});
    console.log(a);
```

[from的其他参数](t/02_array_from2.js)

Array.of() 可以把一组参数转换为数组:
```js
    console.log(Array.of(1, 2, 3, 4));
    console.log(Array.of(undefined));
```

[of转数组示例](t/02_array_of.js)

### 数组空位

使用数组字面量初始化数组时，可以使用一串逗号来创建空位。这些空位被当成存在的元素，只不过值为 undefined:
```js
    const options = [1,,,,5];

    for (const option of options) {
        console.log(option === undefined);
    }
```

### 数组索引

通过 `[]` 可以得到或设置数组的值:
```js
    let colors = ["red", "blue", "green"];
    console.log(colors[0]);
    colors[2] = "black";
```
如果把一个值设置给超过数组最大索引的索引，则数组长度会自动扩展到该索引值加 1:
```js
    colors[3] = "brown";
    colors.length;      // 4
```

数组的 `length` 属性不仅可读，还可以通过修改它，从数组末尾删除或添加元素:
```js
    let colors = ["red", "blue", "green"];
    colors.length = 2;
    console.log(colors[2]); // undefined
```
如果将 length 设置为大于数组元素的值，则新添加的元素都将以 undefined 填充。

使用 length 属性可以方便地向数组末尾添加元素:
```js
    let colors = ["red", "blue", "green"];
    colors[colors.length] = "black";
    colors[colors.length] = "brown";
    console.log(colors.length);     // 5
```

### 检测数组

ES 提供了 `Array.isArray()` 方法来判断一个对象是不是数组:
```js
    if (Array.isArray(value)) {
        // 操作数组
    }
```
