
'use strict';

const m = new Map();

const functionKey = function() {};
const symbolKey = Symbol();
const objectKey = new Object();

m.set(functionKey, "functionValue");
m.set(symbolKey, "symbolValue");
m.set(objectKey, "objectValue");

console.log(m.get(functionKey));
console.log(m.get(symbolKey));
console.log(m.get(objectKey));

console.log(m.get(function(){}));
