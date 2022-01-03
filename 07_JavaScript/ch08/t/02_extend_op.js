
'use strict';

function getProduct(a, b, c = 1) {
    return a * b * c;
}

let getSum = (a, b, c = 0) => {
    return a + b + c;
};

console.log(getProduct(...[1,2]));
console.log(getProduct(...[1,2,3]));
console.log(getProduct(...[1,2,3,4])); 

console.log(getSum(...[0,1]));
console.log(getSum(...[0,1,2]));
console.log(getSum(...[0,1,2,3]));
