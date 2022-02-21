
'use strict';

const s = new Set();

const functionVal = function() {};
const symbolVal = Symbol();
const objectVal = new Object();

s.add(functionVal);
s.add(symbolVal);
s.add(objectVal);

console.log(s.has(functionVal));
console.log(s.has(symbolVal));
console.log(s.has(objectVal));
