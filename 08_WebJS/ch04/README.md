
在 JavaScript 中，调用事件的方式有两种。
* 在 JavaScript 标签中调用
* 在元素中调用

在 script 标签中调用事件，指的是在 `<script></script>` 标签内部调用事件。
```html
    <script>
        window.onload = function()
        {
            var oBtn = docuemnt.getElementById("btn");
            oBtn.onclick = function() {
                alert("点击了按钮");
            };
        }
    </script>
```
这种事件调用方式从本质上来说就是操作元素的属性。只不过这个属性不是一般的属性，而是"事件属性"。

在元素中调用事件，指的是直接在 HTML 属性中来调用属性，这个属性又叫"事件属性"。
```html
    <input type="button" onclick="alert('点击了按钮')" value="弹出" />
```
