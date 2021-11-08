
"use strict";

// 逻辑非
{
    console.log("----- 逻辑非 -----");
    console.log(!false);    // true
    console.log(!"blue");   // false
    console.log(!0);        // true
    console.log(!NaN);      // true
    console.log(!"");       // true
    console.log(!12345);    // false

    console.log(!!"blue");  // true
    console.log(!!0);       // false
    console.log(!!NaN);     // false
    console.log(!!"");      // false
    console.log(!!12345);   // true
}

{
    console.log("----- 逻辑与 -----");

    let i = 100;
    let s = "Hello World";
    let n = null;

    console.log("i && s =", i && s);    // Hello World
    console.log("n && s =", n && s);    // null
}

{
    console.log("----- 逻辑或 -----");

    let i = 100;
    let s = "Hello World";
    let n = null;

    console.log("i && s =", i || s);    // 100
    console.log("n && s =", n || s);    // Hello World
}

{
    console.log("----- 乘法 -----");
    console.log(100 * NaN);             // NaN
    console.log(Infinity * 0);          // NaN
    console.log(Infinity * -10);        // -Infinity
    console.log(Infinity * Infinity);   // Infinity
    console.log("2" * "20");            // 40
}

{
    console.log("----- 除法 -----");
    console.log(100 / NaN);             // NaN
    console.log(NaN / 100);             // NaN
    console.log(Infinity / Infinity);   // NaN
    console.log(0 / 0);                 // NaN
    console.log(-2 / 0);                // -Infinity
    console.log(Infinity / -200);       // -Infinity
    console.log("20" / "10");           // 2
}

{
    console.log("----- 取模 -----");
    console.log(Infinity % 100);        // NaN
    console.log(1 % 0);                 // NaN
    console.log(Infinity % Infinity);   // NaN
    console.log(10 % Infinity);         // 10
    console.log(0 % 10);                // 0
    console.log("26" % "5");            // 1
}

{
    console.log("----- 指数操作符 -----");
    console.log(Math.pow(3, 2));        // 9
    console.log(3 ** 2);                // 9

    console.log(Math.pow(16, 0.5));     // 4
    console.log(16 ** 0.5);             // 4

    let squared = 3;
    squared **= 2;
    console.log(squared);               // 9
}

{
    console.log("----- 加法操作符 -----");
    console.log(NaN + 100);             // NaN
    console.log(Infinity + Infinity);   // Infinity
    console.log(-Infinity + -Infinity); // -Infinity
    console.log(Infinity + -Infinity);  // NaN
    console.log(+0 + +0);               // 0
    console.log(-0 + +0);               // 0
    console.log(-0 + -0);               // -0
    console.log("20" + "2");            // 202
    console.log(30 + "3");              // 303

    let x;
    console.log("30" + x);              //
}

{
    console.log("----- 减法操作符 -----");
    console.log(NaN - 100);             // NaN
    console.log(Infinity - Infinity);   // NaN
    console.log(Infinity - -Infinity);  // Infinity
    console.log(-Infinity - Infinity);  // -Infinity
    console.log(+0 - +0);               // 0
    console.log(+0 - -0);               // 0
    console.log(-0 - -0);               // 0
    console.log("20" - "2");            // 18
    console.log(30 - "3");              // 27
    console.log(5 - null);              // 5
    
    let x;
    console.log("30" - x);              // NaN
}

{
    console.log("----- 关系操作符 -----");
    console.log("23" < "3");    // true 按字典序比较
    console.log("23" < 3);      // false 字符串转数值后比较
    console.log("a" < 3);       // false "a" 转换为 NaN 再比较
    console.log(NaN < 3);       // false
    console.log(NaN >= 3);      // false
}

{
    console.log("----- 等于与不等于 -----");
    console.log(null == undefined); // true
    console.log("NaN" == NaN);      // false
    console.log(5 == NaN);          // false
    console.log(NaN == NaN);        // false
    console.log(NaN != NaN);        // true
    console.log(false == 0);        // true
    console.log(true == 1);         // true
    console.log(true == 2);         // false
    console.log(undefined == 0);    // false
    console.log(null == 0);         // false
    console.log("5" == 5);          // true
}

{
    console.log("----- 全等与不全等 -----");
    console.log("55" === 55);       // false
    console.log("55" !== 55);       // true
    console.log(null === undefined);// false
}