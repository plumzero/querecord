
"use strict";

console.log("--- 弱集合的使用 ---");
{
    const val1 = {id: 1},
          val2 = {id: 2},
          val3 = {id: 3};
    // 使用数组初始化弱集合
    const ws1 = new WeakSet([val1, val2, val3]);

    console.log(ws1.has(val1));
    console.log(ws1.has(val2));
    console.log(ws1.has(val3));

    // 初始化是全有或全无的操作
    // 只要有一个值无效就会抛出错误，导致整个初始化失败
    // const ws2 = new WeakSet([val1, "BADVAL", val3]);
}

console.log("--- 原始值可以先包装成对象再用作值 ---");
{
    const stringVal = new String("val1");
    const ws3 = new WeakSet([stringVal]);
    console.log(ws3.has(stringVal));
}

console.log("--- add/has/delete ---");
{
    const ws = new WeakSet();
    
    const val1 = {id: 1},
          val2 = {id: 2};
    
    console.log(ws.has(val1));
    
    ws.add(val1)
      .add(val2);
    console.log(ws.has(val1));
    console.log(ws.has(val2));
    
    ws.delete(val1);
    console.log(ws.has(val1));
    console.log(ws.has(val2));
}

console.log("--- add 返回弱集合实例 ---");
{
    const val1 = {id: 1},
          val2 = {id: 2},
          val3 = {id: 3};
    
    const ws = new WeakSet().add(val1);

    ws.add(val2)
      .add(val3);

    console.log(ws.has(val1));
    console.log(ws.has(val2));
    console.log(ws.has(val3));
}