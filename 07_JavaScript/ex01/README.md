
### 实现功能

* 点击链接时当页显示，而不是跳转
* 当页显示的同时，也可以看到这张图片以及原有的图片清单

[示例一](image_gallery.html)

[使用挂钩处理示例](image_gallery_hook.html)


### 事件处理

事件处理函数的作用是，在特定事件发生时调用特定的 JavaScript 代码。例如，如果想在鼠标指针悬停在某个元素上时触发一个动作，就需要使用 onmouseover 事件处理函数；如果想在鼠标指针离开某个元素时触发一个动作，就需要使用 onmouseout 事件处理函数；如果想在用户点击某个链接时触发一个动作，需要使用 onclick 事件处理函数。

事件处理函数的工作机制是: 在给某个元素添加了事件处理函数后，一旦事件发生，相应的 JavaScript 代码就会得到执行。被调用的 JavaScript 代码可以返回一个值，这个值将被传递给那个事件处理函数。例如，我们可以给某个链接添加一个 onclick 事件处理函数，并让这个处理函数所触发的 JavaScript 代码返回布尔值 true 或 false。这样一来，当这个链接被点击时，如果那段 JavaScript 代码返回的值是 true，onclick 事件处理函数就认为"这个链接被点击了"。反之，如果返回的值是 false，onclick 事件处理函数就认为"这个链接没有被点击"。
```html
    <a href="http://www.example.com" onclick="return false;">Click me</a>
```


### childNodes 属性

在一棵节点树上，`childNodes` 属性可以用来获取任何一个元素的所有子元素，它是一个包含这个元素全部子元素的数组:
```js
    element.childNodes
```
如，获取 body 元素的所有子元素:
```js
    var body_element = document.getElementsByTagName("body")[0];        // 每份文档只有一个 body 元素，所以位于第一个
    body_element.childNodes;            // 所有子元素
    body_element.childNodes.length;     // 子元素的个数
```

### nodeType 属性

文档树的节点类型有多种，通过 `nodeType` 表示，它是一类数值，其含义如下:

| 节点类型 | 属性值 |
|:--------|:-------|
| 元素节点 | 1 |
| 属性节点 | 2 |
| 文本节点 | 3 |

### nodeValue 属性

可以通过 `nodeValue` 属性来得到(和设置)一个节点的值:
```js
    node.nodeValue
```

### firstChild 和 lastChild 属性

如果需要访问 childNodes 数组的第一个元素，可以写成 `firstChild`:
```js
    node.firstChild
```
这完全等价于:
```js
    node.childNodes[0]
```

如果需要访问 childNodes 数组的最后一个元素，可以写成 `lastChild`:
```js
    node.lastChild
```
这完全等价于:
```js
    node.childNodes[node.childNodes.length-1]
```

