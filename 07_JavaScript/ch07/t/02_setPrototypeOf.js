
'use strict';

const myTarget = {};

const proxy = new Proxy(myTarget, {
    setPrototypeOf(target, prototype) {
        console.log('setPrototypeOf()');
        return Reflect.setPrototypeOf(...arguments);
    }
});

Object.setPrototypeOf(proxy, Object);
