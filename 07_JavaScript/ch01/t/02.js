
"use strict";

{
    let message = "some string";
    console.log(typeof message);      // "string"
    console.log(typeof (message));    // "string"
    console.log(typeof 95);           // "number"
}

{
    console.log(0.1 + 0.2);           // 0.30000000000000004
}

{
    let result = Number.MAX_VALUE + Number.MAX_VALUE;
    console.log(isFinite(result));
}

{
    console.log(isNaN(NaN));        // true
    console.log(isNaN(10));         // false, 10 是数值
    console.log(isNaN("10"));       // false, 可以转换为数值 10
    console.log(isNaN("blue"));     // true, 不可以转换为数值
    console.log(isNaN(true));       // false, 可以转换为数值 1
}

{
    let myMultiLineString = 'first line\nsecond line';
    let myMultiLineTemplateLiteral = `first line
second line`;

    console.log(myMultiLineString);
    console.log(myMultiLineTemplateLiteral);

    console.log(myMultiLineString === myMultiLineTemplateLiteral);
}

{
    let value = 5;
    let exponent = 'second';
    // 以前，字符串插值是这样实现的
    let interpolatedString = value + ' to the ' + exponent + ' power is ' + (value * value);
    // 现在，可以用模板字面量这样实现
    let interpolatedTemplateLiteral = `${ value } to the ${exponent} power is ${value * value}`;
    console.log(interpolatedString);
    console.log(interpolatedTemplateLiteral);
}

{
    function capitalize(word) {
        return `${ word[0].toUpperCase() }${ word.slice(1) }`;
    }
    console.log(`${ capitalize('hello') }, ${ capitalize('world') }!`); // Hello, World!
}