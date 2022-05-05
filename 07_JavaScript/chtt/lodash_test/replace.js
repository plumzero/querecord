
import _ from 'lodash';

// 替换 sting 字符串中匹配的 pattern 为给定的 replacement 。

// _.replace([string=''], pattern, replacement)
// 参数:
//  [string='']: 待替换的字符串
//  pattern: 要匹配的内容，可以是 RegExp 或 string
//  replacement: 要替换的内容
// 返回:
//  返回替换后的字符串

let r = _.replace('Hi Fred', 'Fred', 'Barney');
console.log(r);
