
'use strict';

function ignoreFirst(firstValue, ...values) {
    console.log(values);
}

ignoreFirst();
ignoreFirst(1);
ignoreFirst(1, 2);
ignoreFirst(1, 2, 3);

function getSum(...values) {
    return values.reduce((x, y) => x + y, 0);
}

console.log(getSum(1, 2, 3));
