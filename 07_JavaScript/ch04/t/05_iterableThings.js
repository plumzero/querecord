
"use strict";

console.log("--- 4 种可迭代对象(提供默认迭代) ---");
{
    let iterableThings = [
        Array.of(1, 2),
        Int16Array.of(3, 4),
        new Map([[5, 6], [7, 8]]),
        new Set([9, 10])
    ];

    for (const iterableThing of iterableThings) {
        for (const x of iterableThing) {
            console.log(x);
        }
    }
}

console.log("--- 扩展操作符 ---");
{
    let arr1 = [1, 2, 3];
    let arr2 = [...arr1];
    
    console.log(arr1);
    console.log(arr2);
    console.log(arr1 === arr2);

    // 构建数组的部分元素
    let arr3 = [0, ...arr1, 4, 5];
    console.log(arr3);
}

console.log("--- 对于期待可迭代对象的构造函数，只要传入一个可迭代对象就可以实现复制~ ---");
{
    let map1 = new Map([[1,2], [3,4]]);
    let map2 = new Map(map1);

    console.log(map1);
    console.log(map2);
}

console.log("--- 扩展操作符对实现浅复制很有用，浅复制意味首只会复制对象引用~ ---");
{
    let arr1 = [{}];
    let arr2 = [...arr1];

    arr1[0].foo = 'bar';
    console.log(arr2[0]);   // { foo: 'bar' }
}

console.log("--- 可迭代对象之间的转换 ---");
{
    let arr1 = [1, 2, 3];

    // 把数组复制到定型数组
    let typedArr1 = Int16Array.of(...arr1);
    let typedArr2 = Int16Array.from(arr1);
    console.log(typedArr1);
    console.log(typedArr2);

    // 把数组复制到映射
    let map = new Map(arr1.map((x) => [x, 'val' + x]));
    console.log(map);

    // 把数组复制到集合
    let set = new Set(typedArr2);
    console.log(set);

    // 把集合复制回数组
    let arr2 = [...set];
    console.log(arr2);
}