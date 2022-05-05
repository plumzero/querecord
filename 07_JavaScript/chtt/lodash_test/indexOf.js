
import _ from 'lodash';

// _.indexOf(array, value, [fromIndex = 0])

// 使用 sameValueZero 等值比较，返回首次 value 在数组 array 中被找到的索引值。
// 如果 fromIndex 为负值，将从数组 array 尾端索引进行匹配。

// 参数
//  array: 需要查找的数组
//  value: 需要查找的值
//  [fromIndex = 0]: 开始查询的位置

// 返回值
//  返回值 value 在数组中的索引位置，没有找到则返回 -1

let i = _.indexOf([1, 2, 1, 2], 2);
console.log('i = ', i);

i = _.indexOf([1, 2, 1, 2], 2, 2);
console.log('i = ', i);

i = _.indexOf(['mom', 'and', 'dad', 'and', 'baby'], 'baby');
console.log('i = ', i);
