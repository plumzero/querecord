
'use strict';

const myTarget = {};

const proxy = new Proxy(myTarget, {
    ownKeys(target) {
        console.log('ownKeys()');
        return Reflect.ownKeys(...arguments);
    }
});

Object.keys(proxy);
