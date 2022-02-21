
'use strict';

const s = new Set();

console.log(s.has("Matt"));
console.log(s.size);

s.add("Matt")
 .add("Frisbie");

console.log(s.has("Matt"));
console.log(s.size);

s.delete("Matt");   // 删除一个值

console.log(s.has("Matt"));
console.log(s.has("Frisbie"));
console.log(s.size);

s.clear();  // 清空集合

console.log(s.has("Matt"));
console.log(s.has("Frisbie"));
console.log(s.size);
