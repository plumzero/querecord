
'use strict';

{
    let colors = new Array();

    let count = colors.push("push", "green");
    console.log(count);
    
    count = colors.push("black");
    console.log(count);
    
    let item = colors.pop();
    console.log(item);
    
    console.log(colors.length);
}

// 栈数组可以与数组的其他任何方法一起使用
{
    let colors = ["red", "blue"];
    colors.push("brown");
    colors[3] = "black";
    console.log(colors.length);

    let item = colors.pop();
    console.log(item);
}
