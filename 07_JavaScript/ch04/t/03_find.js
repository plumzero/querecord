
'use strict';

// 测试一
const people = [
    {
        name: "Matt",
        age: 27
    },
    {
        name: "Nicholas",
        age: 29
    }
];

let r = people.find((element, index, array) => element.age < 28);
console.log('r = ', r);
let r2 = people.findIndex((element, index, array) => element.age < 28);
console.log('r2 = ', r2);
let r3 = people.find((element, index, array) => element.age > 38);
console.log('r3 = ', r3);
let r4 = people.find((element) => element.age > 28);
console.log('r4 = ', r4);


// 测试二
const evens = [ 2, 4, 6 ];
// 找到匹配后，永远不会检查数组的最后一个元素
let res = evens.find((element, index, array) => {
    console.log(element, index, array);
    return element === 4;
});
console.log('res = ', res);