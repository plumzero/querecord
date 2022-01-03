
'use strict';

let colors = ["red", "blue", "green"];

// 返回一个以 , 分隔的字符串
console.log(colors.toString(colors));
console.log(colors.toLocaleString(colors));
// valueOf() 返回的还是数组本身
console.log(colors.valueOf());
console.log(colors);

// 通过 || 分隔
console.log(colors.join("||"));
