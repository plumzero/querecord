
'use strict';

const s1 = new Set(["val1"]);

// 字符串原始值作为值不会被修改
for (let value of s1.values()) {
    value = "newVal";
    console.log(value);
    console.log(s1.has("val1"));
}

const valObj = {id: 1};
const s2 = new Set([valObj]);

// 修改值对象的属性，但对象仍然存在于集合中
for (let value of s2.values()) {
    value.id = "newVal";
    console.log(value);
    console.log(s2.has(valObj));
}