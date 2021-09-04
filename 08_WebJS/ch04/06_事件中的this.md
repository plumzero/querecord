
在事件操作中，可以这样理解: 哪个 DOM 对象(元素节点)调用 了 this 所在的函数，那么 this 指向的就是哪个 DOM 对象。

```html
    <script>
        window.onload = function.getElementsByTagName("div")[0];
        oDiv.onclick = function () {
            this.style.color = "hotpink";
        }
    </script>
```
在上例中，this 所在的函数是一个匿名函数，这个匿名函数为 oDiv 所调用，所以 this 指向的就是 oDiv 。

在闭包函数中，要尽量使用 this 而不是 DOM 对象。
