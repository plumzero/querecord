
import _ from 'lodash';

// _.split([string = ''], separator, [limit])

// 根据 separator 拆分字符串 string


// 参数
//  [string = '']: 要拆分的字符串
//  separator: 拆分的分隔符。可以是 RegExp 或 string
//  [limit]: 限制结果的数量

// 返回
//  返回拆分部分的字符串的数组

let arr = _.split('a-b-c', '-');
console.log(arr);

arr = _.split('a-b-c', '-', 2);
console.log(arr);
