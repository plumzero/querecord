
'use strict';

let num = 1;
let obj = {};

// 这两种类型没有实现迭代器工厂函数
console.log(num[Symbol.iterator]);      // undefined
console.log(obj[Symbol.iterator]);      // undefined

let str = 'abc';
let arr = ['a', 'b', 'c'];
let map = new Map().set('a', 1).set('b', 2).set('c', 3);
let set = new Set().add('a').add('b').add('c');

// 这些类型都实现了迭代器工厂函数
console.log(str[Symbol.iterator]);
console.log(arr[Symbol.iterator]);
console.log(map[Symbol.iterator]);
console.log(set[Symbol.iterator]);

// 调用这个工厂函数会生成一个迭代器
console.log(str[Symbol.iterator]());
console.log(arr[Symbol.iterator]());
console.log(map[Symbol.iterator]());
console.log(set[Symbol.iterator]());
