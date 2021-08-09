

功能演示:
* 打开新窗口
* 挂钩分离 JavaScript


### 打开新窗口

JavaScript 使用 window 对象的 `open()` 方法来创建新的浏览器窗口。
```js
    window.open(url, name, features);
```
这个方法有三个参数，这三个参数都是可选的:
* `url`: 想在新窗口里打开的网页的 URL 地址。如果省略这个参数，屏幕上将弹出一个空白的浏览器窗口。
* `name`: 新窗口的名字。可以在代码里通过这个名字与新窗口进行通信。
* `features`: 一个以逗号分隔的字符串，其内容是新窗口的各种属性。这些属性包括新窗口的尺寸(宽度和高度)以及新窗口被启用或禁用的各种浏览功能(工具条、菜单条、初始显示位置，等等)。对于这个参数应该掌握以下原则：新窗口的浏览功能要少而精。

[打开窗口示例](popup.html)

### 分离 javascript

将 HTML 文档与 JavaScript 代码分离是一种很好的做法，不过对于内嵌的事件处理函数，还有一点问题。

在 HTML 文档里使用诸如 `onclick` 之类的属性是一种既没有效率又容易引发问题的做法。如果用一个"挂钩"，就像 CSS 机制中的 class 或 id 属性那样，把 JavaScript 代码调用行为与 HTML 文档的结构和内容分离开，网页就会健壮得多。

可以在外部 JavaScript 文件里把一个事件添加到 HTML 文档中的某个元素上:
```js
    element.event = action...
```
如果想把一个事件添加到某个带有特定 id 属性的元素上，用 getElementById() 就可以解决问题:
```js
    getElementById(id).event = action
```

[挂钩事件处理函数](popup_hook.html)

