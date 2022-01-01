
'use strict';

const myTarget = {};

const proxy = new Proxy(myTarget, {
    isExtensible(target) {
        console.log('isExtensible()');
        return Reflect.isExtensible(...arguments);
    }
});

Object.isExtensible(proxy);
