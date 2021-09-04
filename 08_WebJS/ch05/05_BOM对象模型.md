
### location 对象

在 JavaScript 中，可以使用 window 对象下的 location 子对象来操作当前窗口的 URL。

对于 `location` 对象，我们只需要掌握以下三个属性:

| 属性 | 说明 |
|:-----|:----|
| href | 当前页面地址 |
| search | 当前页面地址 "?" 后面的内容 |
| hash | 当前页面地址 "#" 后面的内容 |

在 JavaScript 中，可以使用 location 对象的 `href` 属性来获取或设置当前页面的地址。

获取当前页面地址示例:
```html
    <script>
        var url = window.location.href;
        document.write("local url: " + url);
    </script>
```

设置当前页面地址:
```html
    <script>
        setTimeout(function() {
            window.location.href = "http://www.example.com";
        }, 2000);
    </script>
```

在 JavaScript 中，可以使用 location 对象的 `search` 属性来获取和设置当前页面地址 "?" 后面的内容。而 "?" 后面的内容，也叫做 query string(查询字符串)，一般用于数据库查询。
```html
    <script>
        document.write(window.locatin.search);
    </script>
```

在 JavaScript 中，可以使用 location 对象的 `hash` 属性来获取和设置当前页面地址 "#" 后面的内容。"#" 一般用于锚点链接。
```html
    <script>
        document.write(window.locatin.hash);
    </script>
```


### navigator 对象

在 JavaScript 中，可以使用 window 对象下的子对象 `navigator` 来获取浏览器的类型。
```js
    window.navigator.userAgent
```

示例:
```html
    <script>
        document.write(window.navigator.userAgent);
    </script>
```
