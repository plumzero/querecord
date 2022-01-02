
'use strict';

const myTarget = () => {};

const proxy = new Proxy(myTarget(), {
    apply(target, thisArg, ...argumentsList) {
        console.log('apply()');
        return Reflect.apply(...arguments);
    }
});

proxy();
