
'use strict';

let ints = [1, 2, 3];

console.log(ints.map(function(i) { return i + 1; }));
console.log(ints.map((i) => { return i + 1 }));