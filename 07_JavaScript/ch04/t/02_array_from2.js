
'use strict';

const old_array = [1, 2, 3, 4];
const new_array = Array.from(old_array, x => x**2);
console.log(old_array);
console.log(new_array);

const a1 = [1, 2, 3, 4];
const a = Array.from(a1, function(x) { return x**this.exponent }, {exponent: 3});
console.log(a);