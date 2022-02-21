
'use strict';

const m = new Map([
    ["key1", "val1"],
    ["key2", "val2"],
    ["key3", "val3"]
]);

console.log(m.entries === m[Symbol.iterator]);

for (let pair of m.entries()) {
    console.log(pair);
}

for (let pair of m[Symbol.iterator]()) {
    console.log(pair);
}

// 有了迭代器，映射就可以转数组
console.log([...m]);
