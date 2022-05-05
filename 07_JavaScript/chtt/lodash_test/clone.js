
import _ from 'lodash';

// _.clone(value)

// 创建一个 value 的浅拷贝。

// 注意: arguments 对象的可枚举属性会拷贝为普通对象。
// 参数:
//  value: 要拷贝的值
// 返回:
//  拷贝后的值

var objects = [{ 'a': 1 }, { 'b': 2 }];
var shallow = _.clone(objects);

console.log(shallow == objects);        // false 数组是新创建的，数组中的元素是引用类型
console.log(shallow[0] === objects[0]);
console.log(shallow[1] === objects[1]);
