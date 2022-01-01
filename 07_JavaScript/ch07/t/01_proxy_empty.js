
'use strict';

const target = {
    id: 'target'
};

const handler = {};

const proxy = new Proxy(target, handler);

// id 属性会访问同一个值
console.log(target.id)
console.log(proxy.id)

// 给目标属性赋值会反映在两个对象上
// 因为两个对象访问的是同一个值
target.id = 'foo';
console.log(target.id);
console.log(proxy.id);

// 给代理属性赋值会反映在两个对象上
// 因为这个赋值会转移到目标对象
proxy.id = 'bar';
console.log(target.id);
console.log(proxy.id);

// hasOwnProperty() 方法在两个地方
console.log(target.hasOwnProperty('id'));
console.log(proxy.hasOwnProperty('id'));

// Proxy.prototype 是 undefined
// 因此不能使用 instanceof 操作符
// console.log(target instanceof Proxy);
// console.log(proxy instanceof Proxy);

// 严格相等可以用来区分代理和目标
console.log(target == proxy);
console.log(target === proxy);
