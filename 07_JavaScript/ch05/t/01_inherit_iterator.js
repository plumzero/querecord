
'use strict';

class FooArray extends Array {}

let fooArr = new FooArray('foo', 'bar', 'baz');

for (let el of fooArr) {
    console.log(el);
}