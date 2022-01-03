
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


