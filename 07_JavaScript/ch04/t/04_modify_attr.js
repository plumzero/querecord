
'use strict';

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