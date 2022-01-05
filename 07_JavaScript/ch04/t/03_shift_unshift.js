
'use strict';

// 当作队列
{
    let colors = new Array();
    let count = colors.push("red", "green");
    console.log(count);

    count = colors.push("black");
    console.log(count);

    let item = colors.shift();
    console.log(item);
    console.log(colors.length);
}

{
    let colors = new Array();
    let count = colors.unshift("red", "green");
    console.log(count);

    count = colors.unshift("black");
    console.log(count);

    let item = colors.pop();
    console.log(item);
    console.log(colors.length);
}