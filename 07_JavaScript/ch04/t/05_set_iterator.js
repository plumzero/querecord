
'use strict';

const s = new Set(["val1", "val2", "val3"]);

console.log(s.values == s[Symbol.iterator]);
console.log(s.keys === s[Symbol.iterator]);

for (let value of s.values()) {
    console.log(value);
}

for (let value of s[Symbol.iterator]()) {
    console.log(value);
}

// 扩展操作
console.log([...s]);