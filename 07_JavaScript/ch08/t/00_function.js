
'use strict';

function foo() {}
let bar = function() {};
let baz = () => {};

console.log(foo.name);
console.log(bar.name);
console.log(baz.name);
console.log((() => {}).name);