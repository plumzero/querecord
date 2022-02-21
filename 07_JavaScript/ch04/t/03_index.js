
'use strict';

// 数值数组
let numbers = [1, 2, 3, 4, 5, 4, 3, 2, 1];

console.log(numbers.indexOf(4));
console.log(numbers.lastIndexOf(4));
console.log(numbers.includes(4));

console.log(numbers.indexOf(4, 4));
console.log(numbers.lastIndexOf(4, 4));
console.log(numbers.includes(4, 7));

// 对象数组
let person = { name: "Nicholas" };
let people = [ { name: "Nicholas" } ];
let morePeople = [person];

console.log(people.indexOf(person));
console.log(morePeople.indexOf(person));
console.log(people.includes(person));
console.log(morePeople.includes(person));
