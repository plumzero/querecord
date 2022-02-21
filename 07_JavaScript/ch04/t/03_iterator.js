
'use strict';

let numbers = [1, 2, 3, 4, 5, 4, 3, 2, 1];

let everyResult = numbers.every((item, index, array) => item > 2);
console.log(everyResult);

let someResult = numbers.some((item, index, array) => item > 2);
console.log(someResult);

let filterResult = numbers.filter((item, index, array) => item > 2);
console.log(filterResult);

let mapResult = numbers.map((item, index, array) => item * 2);
console.log(mapResult);

numbers.forEach((item, index, array) => {
    console.log(item);
});

console.log(numbers);
