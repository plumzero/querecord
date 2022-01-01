
'use strict';

const target = {
    foo: 'bar',
    x: 'y'
};

// 定义处理程序对象
// 在对象中定义一个名称为 get 的捕获器
const handler = {
    // 捕获器在处理程序对象中以方法名为键
    get() {
        return 'handler override';
    }
};

const proxy = new Proxy(target, handler);

// proxy.property
console.log(target.foo);        // bar
console.log(proxy.foo);         // handler override

// proxy[property]
console.log(target['foo']);     // bar
console.log(proxy['foo']);      // handler override

// Object.create(proxy)[property]
console.log(Object.create(target)['foo']);
console.log(Object.create(proxy)['foo']);
