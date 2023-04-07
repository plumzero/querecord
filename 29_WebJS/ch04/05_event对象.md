
当一个事件发生的时候，这个事件有关的详细都会临时保存在一个指定的地方，这个地方就是 `event` 对象。

每一个事件，都有一个对应的 event 对象。在 JavaScript 中，可以通过 event 对象来获取一个事件的详细信息。其中 event 对象的常用属性如下:

| 属性 | 说明 |
|:----|:------|
| type | 事件类型 |
| keyCode | 键码值 |
| shiftKey | 是否按下 Shift 键 |
| ctrlKey | 是否按下 Ctrl 键 |
| altKey | 是否按下 Alt 键 |

使用 event 对象的 type 属性来获取事件的类型:
```html
    <script>
        window.onload = function ()
        {
            var oBtn = document.getElementById("btn");
            oBtn.onclick = function (evt) {
                alert(e.type);
            };
        }
    </script>
```

event.keyCode 返回的是一个数值，表示键码。常用的按键及对应的键码如下:

| 按键 | 键码 |
|:-----|:-----|
| W    | 87   |
| S    | 83   |
| A    | 65   |
| D    | 68   |
| ↑    | 38   |
| ↓    | 40   |
| ←    | 37   |
| →    | 39   |

```html
    <script>
    window.onload = function ()
    {
        var oSpan = document.getElementsByTagName("span")[0];

        window.addEventListener("keydown", function(evt) {
            if (evt.keyCode == 38 || e.keyCode == 87) {
                oSpan.innerHTML = "上";
            } else if ...
        }, false)
    }
    </script>
```

如果是 Shift、Ctrl 和 Alt 这三个键，可以直接通过 shiftKey、ctrlKey 和 altKey 这三个属性获取。
```html
    // 禁用 Shift Alt Ctrl 键
    <script>
        window.onload = function() 
        {
            document.onkeydown = function(evt) {
                if (evt.shiftKey || evt.altKey || evt.ctrlKey) {
                    // do nothing
                }
            }
        }
    </script>
```
