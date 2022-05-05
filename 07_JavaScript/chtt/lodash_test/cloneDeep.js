
import _ from 'lodash';

// _.cloneDeep(value)

// 创建一个 value 的深拷贝。

// 参数:
//  value: 要深拷贝的值
// 返回:
//  拷贝后的值

var objects = [{ 'a': 1 }, { 'b': 2 }];
var deep = _.cloneDeep(objects);

console.log(deep == objects);
console.log(deep[0] === objects[0]);
console.log(deep[1] === objects[1]);
