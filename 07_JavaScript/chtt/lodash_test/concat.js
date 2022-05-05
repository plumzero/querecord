
import _ from 'lodash';

// _.concat(array, [values])

// 创建一个新数组，将 array 与任何数组或值连接在一起。

// 参数
//  array: 被连接的数组
//  [values]: 连接的值

// 返回值
//  返回连接后的数组

var array = [ 1 ];
var other = _.concat(array, 2, [3], [[4]]);

console.log(other);
console.log(array);