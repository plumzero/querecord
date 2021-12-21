
"use strict";

{
    // 使用数组初始化集合
    const s1 = new Set(["val1", "val2", "val3"]);
    console.log(s1.size);

    // 使用自定义迭代器初始化集合
    const s2 = new Set({
        [Symbol.iterator]: function*() {
            yield "val1";
            yield "val2";
            yield "val3";
        }
    });
    console.log(s2.size);
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const s = new Set();

    console.log(s.has("Matt"));
    console.log(s.size);

    s.add("Matt")
     .add("Frisbie");
    console.log(s.has("Matt"));
    console.log(s.size);

    s.delete("Matt");
    console.log(s.has("Matt"));
    console.log(s.has("Frisbie"));
    console.log(s.size);

    s.clear();
    console.log(s.has("Matt"));
    console.log(s.has("Frisbie"));
    console.log(s.size);
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const s = new Set();

    const functionVal = function() {};
    const symbolVal = Symbol();
    const objectVal = new Object();

    s.add(functionVal);
    s.add(symbolVal);
    s.add(objectVal);

    console.log(s.has(functionVal));
    console.log(s.has(symbolVal));
    console.log(s.has(objectVal));

    // SameValueZero 检查意味首独立的实例不会冲突
    console.log(s.has(function(){}));
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const s = new Set();

    const objVal = {},
          arrVal = [];
    
    s.add(objVal);
    s.add(arrVal);

    objVal.bar = "bar";
    arrVal.push("bar");

    console.log(s.has(objVal));
    console.log(s.has(arrVal));
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const s = new Set();

    s.add('foo');
    console.log(s.size);
    
    s.add('foo');
    console.log(s.size);

    // 集合里有这个值
    console.log(s.delete('foo'));

    // 集合里没有这个值
    console.log(s.delete('foo'));
}

// keys 和 values 是集合迭代器 Symbol.iterator 的别名
console.log("--- keys 和 values 是集合迭代器 Symbol.iterator 的别名 ---");
{
    const s = new Set(["val1", "val2", "val3", "val2"]);

    console.log(s.values == s[Symbol.iterator]);
    console.log(s.keys   == s[Symbol.iterator]);

    for (let value of s.values()) {
        console.log(value);
    }

    for (let value of s[Symbol.iterator]()) {
        console.log(value);
    }
}

console.log("--- 利用迭代器，可以将集合转为数组 ---");
{
    const s = new Set(["val1", "val2", "val3", "val2"]);

    console.log([...s]);
}

console.log("--- 也提供了 entries() 方法，但是对于集合感觉用处不大  ---");
{
    const s = new Set(["val1", "val2", "val3", "val2"]);

    for (let pair of s.entries()) {
        console.log(pair);
    }
}

console.log("--- 利用 forEach() 方法传入回调 ---");
{
    const s = new Set(["val2", "val1", "val3", "val2"]);

    s.forEach((val) => console.log(`this is ${val}`));
    s.forEach((val, dupVal) => console.log(`this is ${val}, and its index is ${dupVal}`));
}
