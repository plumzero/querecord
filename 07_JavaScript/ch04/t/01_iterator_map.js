
"use strict";

{
    const m = new Map([
        ["key1", "val1"],
        ["key2", "val2"],
        ["key3", "val3"]
    ]);

    console.log(m.entries == m[Symbol.iterator]);

    for (let pair of m.entries()) {
        console.log(pair);
    }

    for (let pair of m[Symbol.iterator]()) {
        console.log(pair);
    }
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map([
        ["key1", "val1"],
        ["key2", "val2"],
        ["key3", "val3"]
    ]);

    console.log([...m]);
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map([
        ["key1", "val1"],
        ["key2", "val2"],
        ["key3", "val3"]
    ]);

    m.forEach((val, key) => console.log(`${key} -> ${val}`));
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map([
        ["key1", "val1"],
        ["key2", "val2"],
        ["key3", "val3"]
    ]);

    for (let key of m.keys()) {
        console.log(key);
    }

    for (let key of m.values()) {
        console.log(key);
    }
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m1 = new Map([
        ["key1", "val1"]
    ]);

    // 作为键的字符串原始值是不能修改的
    for (let key of m1.keys()) {
        key = "newKey";
        console.log(key);
        console.log(m1.get("key1"));
    }

    const keyObj = {id: 1};
    const m = new Map([
        [keyObj, "val1"]
    ]);

    // 修改了作为键的对象的属性，但对象在映射内部仍然引用相同的值
    for (let key of m.keys()) {
        key.id = "newKey";
        console.log(key);
        console.log(m.get(keyObj));
    }
    console.log(keyObj);
}
