
'use strict';

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

console.log(people.find((element, index, array) => element.age < 28));
console.log(people.findIndex((element, index, array) => element.age < 28));

const evens = [ 2, 4, 6 ];
// 找到匹配后，永远不会检查数组的最后一个元素
evens.find((element, index, array) => {
    console.log(element);
    console.log(index);
    console.log(array);
    return element === 4;
});