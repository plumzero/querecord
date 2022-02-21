
'use strict';

let arr = ['foo', 'bar', 'baz'];

// for-of 循环
for (let el of arr) {
    console.log(el);
}

// 数组解构
let [a, b, c] = arr;
console.log(a, b, c);

// 扩展操作符
let arr2 = [...arr];
console.log(arr2);

// Array.from()
let arr3 = Array.from(arr);
console.log(arr3);

// Set 构造函数
let set = new Set(arr);
console.log(set);

// Map 构造函数
let pairs = arr.map((x, i) => [x, i]);
console.log(pairs);
let map = new Map(pairs);
console.log(map);

