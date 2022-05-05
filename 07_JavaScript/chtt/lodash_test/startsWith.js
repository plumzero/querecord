
import _ from 'lodash';

// _.startsWith([string = ''], [target], [position = 0])

// 检查字符串 string 是否以 target 开头

// 参数
//  [string = '']: 要检索的字符串
//  [target]: 要检查的字符串
//  [position = 0]: 检索的位置

// 返回值
//  如果 string 以 target 开头，则返回 true，否则返回 false 。

let bl = _.startsWith('abc', 'a');
console.log(bl);

bl = _.startsWith('hello world', 'he');
console.log(bl);
