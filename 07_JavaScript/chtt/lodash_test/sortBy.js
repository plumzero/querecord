
import _ from 'lodash';

// _.sortBy(collection, [iteratees = [_.identity]])

// 创建一个元素数组。以 iteratees 处理的结果升序排序。
// 这个方法执行稳定排序。
// iteratees 调用 1 个参数: (value)

// 该方法的执行不会影响原来的数组。

// 参数
//  collection (Array|Object): 用来迭代的集合
//  [iteratees = [_.identity]]: 决定排序的函数

// 返回
//  返回排序后的数组

var users = [
    { 'user': 'fred', 'age': 48 },
    { 'user': 'barney', 'age': 36 },
    { 'user': 'fred', 'age': 40 },
    { 'user': 'barney', 'age': 34 }
];

let s = _.sortBy(users, (o) => { return o.user });
console.log(s);

s = _.sortBy(users, [ 'user', 'age' ]);
console.log(s);
