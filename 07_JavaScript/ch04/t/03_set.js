
"use strict";

{
    // 使用数组初始化集合
    const s1 = new Set(["val1", "val2", "val3"]);
    console.log(s1.size);

    // 使用自定义迭代器初始化集合
    const s2 = new Set({
        [Symbol.iterator]: function*() {
            yield "val1";
            yield "val2";
            yield "val3";
        }
    });
    console.log(s2.size);
}

// --- 分割线 ---
console.log("--- 分割线 ---");
{
    const s = new Set();

    console.log(s.has("Matt"));
    console.log(s.size);

    s.add("Matt")
     .add("Frisbie");
    console.log(s.has("Matt"));
    console.log(s.size);

    s.delete("Matt");
    console.log(s.has("Matt"));
    console.log(s.has("Frisbie"));
    console.log(s.size);

    s.clear();
    console.log(s.has("Matt"));
    console.log(s.has("Frisbie"));
    console.log(s.size);
}