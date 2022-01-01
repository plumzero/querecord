
'use strict';

const myTarget = {};

const proxy = new Proxy(myTarget, {
    getPrototypeOf(target) {
        console.log('getPrototypeOf()');
        return Reflect.getPrototypeOf(...arguments);
    }
});

Object.getPrototypeOf(proxy);
