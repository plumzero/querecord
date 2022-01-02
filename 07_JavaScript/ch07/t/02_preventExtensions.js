
'use strict';

const myTarget = {};

const proxy = new Proxy(myTarget, {
    preventExtensions(target) {
        console.log('preventExtensions()');
        return Reflect.preventExtensions(...arguments)
    }
});

Object.preventExtensions(proxy)
