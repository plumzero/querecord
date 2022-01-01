
'use strict';

const myTarget = {};

const proxy = new Proxy(myTarget, {
    has(target, property) {
        console.log('has()');
        return Reflect.has(...arguments);
    }
});

'foo' in proxy;
