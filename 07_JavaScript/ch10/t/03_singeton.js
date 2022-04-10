
var a1 = require('./moduleA');
var a2 = require('./moduleA');

console.log(a1 === a2);     // true

console.log(a1.foo);
a2.stuff();
