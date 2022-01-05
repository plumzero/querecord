
'use strict';

let colors = ["red", "green", "blue"];

let removed = colors.splice(0, 1);      // 删除第一项

console.log(colors);
console.log(removed);

removed = colors.splice(1, 0, "yellow", "orange");  // 在位置 1 插入两个元素
console.log(colors);
console.log(removed);

removed = colors.splice(1, 2, "red", "purple");     // 替换: 删除两个元素，插入两个元素
console.log(colors);
console.log(removed);
