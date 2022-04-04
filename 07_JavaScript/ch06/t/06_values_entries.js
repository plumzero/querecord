
const o = {
    foo: 'bar',
    baz: 1,
    qux: {}
};

console.log(Object.values(o));
console.log(Object.entries(o));

// 浅复制
const o2 = {
    qux: {}
};

console.log(Object.values(o2)[0] === o2.qux);
console.log(Object.entries(o2)[0][1] === o2.qux);

// 符号属性会被忽略
const sym = Symbol();
const o3 = {
    [sym]: 'foo'
};

console.log(Object.values(o3));
console.log(Object.entries(o3));
