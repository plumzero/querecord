
// 常见的伪数组有 arguments 和 DOM 对象列表。
// 相比于数组，伪数组缺少操作数组的很多方法

/*
<ul class="list">
    <li></li>
    <li></li>
    <li></li>
</ul>
*/

// 对于上述 html 文档，可以进行如下操作

let li = document.querySelectorAll('.list > li');
let res = Array.prototype.slice.all(li);    // 也可以使用 Array.from(li) 转为数组
console.log(res);
