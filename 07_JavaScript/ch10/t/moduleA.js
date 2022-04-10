
console.log('moduleA');
var moduleB = require('./moduleB');

module.exports = {
    foo: 'A-' + moduleB.foo,
    stuff: moduleB.doStuff      // 注意，不能写成 moduleB.doStuff() ，这会变成一个对象在加载时立即执行，但实际上我们并不想这样
};

