
'use strict';

let values = [1, 2, 3, 4, 5];
let sum = values.reduce((prev, cur, index, array) => prev + cur);
console.log(sum);

let sumRight = values.reduceRight(function(prev, cur, index, array) {
    return prev + cur;
});
console.log(sumRight);
