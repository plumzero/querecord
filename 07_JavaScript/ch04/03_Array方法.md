
### 迭代器方法

在 ES6 中 Array 的原型暴露了 3 个用于检索数组内容的方法，它们都返回一个迭代器:
- `keys()`: 返回数组索引的迭代器
- `values()`: 返回数组元素的迭代器
- `entries()`: 返回索引/值对的迭代器

[检索数组内容的方法示例](t/03_array_iterator.js)

### 复制和填充方法

ES6 新增了两个方法，批量复制方法 `copyWithin()` 以及填充数组方法 `fill()`。这两个方法不会改变数组的大小，不过都需要指定既有数组实例上的一个范围。
```js
    const zeroes = [0, 0, 0, 0, 0];

    // 用 5 填充整个数组
    zeroes.fill(5);
    zeroes.fill(0);     // 重置
    // 用 6 填充索引大于等于 3 的元素
    zeroes.fill(6, 3);
    zeroes.fill(0);     // 重置
    // 用 7 填充索引大于等于 1 且小于 3 的元素
    zeroes.fill(7, 1, 3);
    zeroes.fill(0);     // 重置
    // 用 8 填充索引大于等于 1 且小于 4 的元素
    zeroes.fill(8, -4, -1);
```

与 fill() 不同，copyWithin() 会按照指定范围浅复制数组中的部分内容，然后将它们插入到指定索引开始的位置。
```js
    let ints,
        reset = () => ints = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
    reset();

    // 从 ints 中复制索引 5 开始的内容，插入到索引 0 开始的位置
    ints.copyWithin(0, 5);
    console.log(ints);
    reset();

    // 从 ints 中复制索引 0 开始到索引 3 结束的内容
    // 插入到索引 4 开始的位置
    ints.copyWithin(4, 0, 3);
    console.log(ints);
    reset();

    // JavaScript 引擎在插值前会完整复制范围内的值
    // 因此复制期间不存在重写的风险
    ints.copyWithin(2, 0, 6);
    console.log(ints);
    reset();
```

[copyWithin方法示例](t/03_copyWithin.js)

### 转换方法

继承的方法 `toLocaleString()` 以及 `toString()` 都返回数组值的逗号分隔的字符串。如果想使用不同的分隔符，则可以使用 `join()` 方法。
```js
    let colors = ["red", "blue", "green"];

    // 返回一个以 , 分隔的字符串
    console.log(colors.toString(colors));           // red,blue,green
    console.log(colors.toLocaleString(colors));     // red,blue,green
    // 通过 || 分隔
    console.log(colors.join("||"));
```

### 栈方法

ES 数组提供了 push() 和 pop() 方法，以实现类似栈的行为。

`push()` 方法接收任意数量的参数，将将它们添加到数组末尾，返回数组的最新长度。`pop()` 方法则用于删除数组的最后一项，同时减少数组的 length 值，返回被删除的值。

[push和pop示例](t/03_push_pop.js)

### 队列方法

`shift()` 会删除数组的第一项并返回它，然后数组长度减 1。使用 shift() 和 push()，可以把数组当成队列来使用。

ES 也提供了 `unshift()` 方法，它执行跟 shift() 相反的操作: 在数组开头添加任意多个值，然后返回新的数组长度。

[shift和unshift示例](t/03_shift_unshift.js)


### 排序方法

数组有两个方法可以用来对元素重新排序: `reverse()` 和 `sort()`。reverse() 方法是将数组元素反向排列。

sort() 会在每一项上调用 String() 转型函数，然后比较字符串来决定顺序。即使数组的元素都是数值，也会先把数组转换为字符串再比较、排序。
```js
    let values = [0, 1, 5, 10, 15];
    values.sort();
    console.log(values);    // 0, 1, 10, 15, 5
```

为此，sort() 方法可以接收一个比较函数，用于判断哪个值应该排在前面。

比较函数接收两个参数，如果第一个参数应该排在第二个参数前面，就返回负值；如果两个参数相等，就返回 0；如果第一个参数应该排在第二个参数后面，就返回正值。

[使用比较函数](t/03_sort_compare.js)

reverse() 和 sort() 都返回调用它们的数组的引用。

### 操作方法

`contact()` 方法可以在现在数组全部元素基础上创建一个新数组。它首先会创建一个当前数组的副本，然后再把它的参数添加到副本末尾，最后返回这个新构建的数组。如果传入一个或多个数组，则 contact() 会把这些数组的第一项都添加到结果数组。如果参数不是数组，则直接把它们添加到结果数组末尾。

contact() 在以数组作为参数时，会对结果进行打平。通过 `Symbol.isConcatSpreadable` 可以阻止打平。

[contact()方法示例](t/03_contact.js)

`splice()` 方法用于创建一个包含原有数组中一个或多个元素的新数组。它可以接收一个或两个参数: 返回元素的开始索引和结束索引。如果只有一个参数，则 slice() 会返回该索引到数组末尾的所有元素。如果有两个参数，则 slice() 返回从开始索引到结束索引对应的所有元素，其中不包含结束索引对应的元素。

slice() 操作不影响原始数组。

[slice()方法示例](t/03_slice.js)

splice() 的主要目的是在原数组中间插入元素，有 3 种不同的方式:
- 删除: 传入两个参数，要删除的第一个元素的位置和要删除的元素数量。比如 splice(0,2) 会删除前两个元素。
- 插入: 传入三个参数，开始位置，0(要删除的元素数量)和要插入的元素，第三个参数之后可以传第四个、第五个参数，乃至任意多个要插入的元素。
- 替换: 传入三个参数，开始位置，0(要删除的元素数量)和要插入的元素。要插入的元素数量不一定跟删除的元素数量一致。

[splice()方法示例](t/03_splice.js)

### 搜索和位置方法

ES 提供两类搜索数组的方法: 按严格相等搜索和按断言函数搜索。

