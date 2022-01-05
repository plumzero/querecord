
'use strict';

{
    let colors = ["red", "green", "blue"];
    let colors2 = colors.concat("yellow", ["black", "brown"]);
    
    console.log(colors);
    console.log(colors2);
}

// 阻止打平
{
    let colors = ["red", "green", "blue"];
    let newColors = ["black", "brown"];

    let moreNewColors = {
        [Symbol.isConcatSpreadable]: true,
        length: 2,
        0: "pink",
        1: "cyan"
    };

    newColors[Symbol.isConcatSpreadable] = false;

    // 强制不打平数组
    let colors2 = colors.concat("yellow", newColors);

    // 强制打平类数组对象
    let colors3 = colors.concat(moreNewColors);

    console.log(colors);
    console.log(colors2);
    console.log(colors3);
}