
'use strict';

const s = new Set();

const objVal = {},
      arrVal = [];
    
s.add(objVal);
s.add(arrVal);

objVal.bar = "bar";
arrVal.push("bar");

console.log(s.has(objVal));
console.log(s.has(arrVal));
