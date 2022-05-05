
import _ from 'lodash';

// _.remove(array, [predicate = _.identity])

// 移除数组中 predicate(断言) 返回为真值的'所有元素'，并返回移除元素组成的数组。
// predicate 会传入 3 个参数: (value, index, array)

// 参数
//  array: 要修改的数组
//  [predicate = _.identity]: 每次迭代调用的函数

// 返回
//  返回移除元素组成的数组

var array = [1, 2, 3, 4];
var evens = _.remove(array, (element) => { return element % 2 == 0; });
console.log('array: ', array);
console.log('evens: ', evens);

var users = [
    { 'user': 'barney', 'age': 36, 'active': true },
    { 'user': 'fred', 'age': 40, 'active': false },
    { 'user': 'pebbles', 'age': 1, 'active': true }
];

var unacs = _.remove(users, (element) => { return element.active == false; });
console.log('users: ', users);
console.log('unacs: ', unacs);
