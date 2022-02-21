
'use strict';

// 使用嵌套数组初始化映射
const m1 = new Map([
    ["key1", "val1"],
    ["key2", "val2"],
    ["key3", "val3"]
]);
console.log(m1.size);

// 使用自定义迭代器初始化映射
const m2 = new Map({
    [Symbol.iterator]: function*() {
        yield ["key1", "val1"];
        yield ["key2", "val2"];
        yield ["key3", "val3"];
    }
});
console.log(m2.size);

// 把数组复制到映射
let arr1 = [1, 2, 3];
let map = new Map(arr1.map((x) => [x, 'val' + x]));
console.log(map);
