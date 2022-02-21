
"use strict";

const m1 = new Map([
    ["key1", "val1"],
    ["key2", "val2"],
    ["key3", "val3"]
]);

console.log("m1.size=", m1.size);

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map();

    console.log(m.has("firstName"));
    console.log(m.get("firstName"));
    console.log(m.size);
    
    m.set("firstName", "Matt")
     .set("lastName", "Frisbie");
    
    console.log(m.has("firstName"));
    console.log(m.get("firstName"));
    console.log(m.size);
    
    m.delete("firstName");
    console.log(m.has("firstName"));
    console.log(m.has("lastName"));
    console.log(m.size);
    
    m.clear();
    console.log(m.has("firstName"));
    console.log(m.has("lastName"));
    console.log(m.size);
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map().set("key1", "val1");

    m.set("key2", "val2")
     .set("key3", "val3");

    console.log(m.size);
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map();

    const functionKey = function(){};
    const symbolKey = Symbol();
    const objectKey = new Object();

    m.set(functionKey, "functionValue");
    m.set(symbolKey, "symbolValue");
    m.set(objectKey, "objectValue");

    console.log(m.get(functionKey));
    console.log(m.get(symbolKey));
    console.log(m.get(objectKey));
    console.log(m.get(function(){}));
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map();

    const objKey = {},
          objVal = {},
          arrKey = [],
          arrVal = [];

    m.set(objKey, objVal);
    m.set(arrKey, arrVal);

    objKey.foo = "foo";
    objVal.bar = "bar";
    arrKey.push("foo");
    arrVal.push("bar");

    console.log(m.get(objKey));
    console.log(m.get(arrKey));
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const m = new Map();

    const a = 0/"",     // NaN
          b = 0/"",     // NaN
         pz = +0,
         nz = -0;
    
    console.log(a === b);
    console.log(pz === nz);

    m.set(a, "foo");
    m.set(pz, "bar");

    console.log(m.get(b));
    console.log(m.get(nz));
}
