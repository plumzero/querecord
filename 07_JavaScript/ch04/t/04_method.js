
'use strict';

const m = new Map();

console.log(m.has("firstName"));
console.log(m.get("firstName"));
console.log(m.size);

m.set("firstName", "Matt")
 .set("lastName", "Frisbie");

console.log(m.has("firstName"));
console.log(m.get("firstName"));
console.log(m.size);

m.delete("firstName"); // 删除一个

console.log(m.has("firstName"));
console.log(m.has("lastName"));
console.log(m.size);

m.clear();      // 清空所有

console.log(m.has("firstName"));
console.log(m.has("lastName"));
console.log(m.size);
