
import _ from 'lodash';

// _.findIndex(array, [predicate = _.identity], [fromIndex = 0])

// 该方法类似 _.find，区别是该方法返回第一个通过 predicate 判断为真值的元素的索引值(index)，而不是元素本身。

// 参数
//  array: 要搜索的数组
//  [predicate = _.identity]: 这个函数会在每一次迭代调用
//  [fromIndex = 0]: 开始搜索的索引位置

// 返回值
//  返回找到元素的索引值，否则返回 -1

var users = [
    { 'user': 'barney', 'age': 36, 'active': true },
    { 'user': 'fred', 'age': 40, 'active': false },
    { 'user': 'pebbles', 'age': 1, 'active': true }
];

let i = _.findIndex(users, function(o) { return o.age < 40; });
console.log('-> ', i);

i = _.findIndex(users, { 'age': 1, 'active': true });
console.log('-> ', i);

i = _.findIndex(users, (element) => element.age < 2);
console.log('-> ', i);
