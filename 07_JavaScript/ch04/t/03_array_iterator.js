
'use strict';

const a = ["foo", "bar", "baz", "qux"];

const aKeys = Array.from(a.keys());
const aValues = Array.from(a.values());
const aEntries = Array.from(a.entries());

console.log(aKeys);
console.log(aValues);
console.log(aEntries);

for (const [idx, element] of a.entries()) {
    console.log(idx, "=>", element);
}
