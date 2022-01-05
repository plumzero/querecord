
'use strict';

function compare(v1, v2) {
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

let values = [ 0, 1, 5, 10, 15 ];
values.sort(compare);
console.log(values);


// 对象排序
function createComparisonFunction(propertyName) {
    return function(object1, object2) {
        let value1 = object1[propertyName];
        let value2 = object2[propertyName];

        if (value1 < value2) {
            return -1;
        } else if (value1 > value2) {
            return 1;
        } else {
            return 0;
        }
    };
}

let data = [
    {name: "Zachary", age: 28},
    {name: "Nicholas", age: 29}
];

data.sort(createComparisonFunction("name"));
console.log(data[0].name);

data.sort(createComparisonFunction("age"));
console.log(data[0].name);
