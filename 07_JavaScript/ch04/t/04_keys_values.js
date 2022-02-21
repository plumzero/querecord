
'use strict';

const m = new Map([
    ["key1", "val1"],
    ["key2", "val2"],
    ["key3", "val3"]
]);

for (let key of m.keys()) {
    console.log(key);
}

for (let key of m.values()) {
    console.log(key);
}