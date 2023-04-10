
### DOM 方法与文档的作用原理

DOM 是文档的表示。DOM 所包含的信息与文档里的信息一一对应。DOM 不仅可以获取文档的内容，还可以更新文档的内容。如果你改变了 DOM 节点树，文档在浏览器里的呈现效果就会发生变化。比如用 setAttribute 方法改变了 DOM 节点树上的某个属性节点后，相关文档在浏览器里的呈现就会发生相应的变化。不过，setAttribute 方法并未改变文档的物理内容，只有在用浏览器打开那份文档时才能看到文档呈现效果的变化。这是因为浏览器实际显示的是那棵 DOM 节点树。在浏览器看来，DOM 节树才是文档。

所以通过 DOM 创建标记其实就是在改变 DOM 节点树。在 DOM 看来，一个文档就是一棵节点树。如果你想在节点树上添加内容，就必须插入新的点。如果你想添加一些标记到文档，就必须插入元素节点。

DOM 利用 `getElementById` 和 `getElementsByTagName` 找到文档中的某个或某些特定的元素节点，这些元素随后可以用诸如 `setAttribute`(改变某个属性的值)和 `nodeValue`(改变某个元素节点所包含的文本)之类的方法和属性来处理。


### 事件处理

事件处理函数的作用是，在特定事件发生时调用特定的 JavaScript 代码。例如，如果想在鼠标指针悬停在某个元素上时触发一个动作，就需要使用 onmouseover 事件处理函数；如果想在鼠标指针离开某个元素时触发一个动作，就需要使用 onmouseout 事件处理函数；如果想在用户点击某个链接时触发一个动作，需要使用 onclick 事件处理函数。

事件处理函数的工作机制是: 在给某个元素添加了事件处理函数后，一旦事件发生，相应的 JavaScript 代码就会得到执行。被调用的 JavaScript 代码可以返回一个值，这个值将被传递给那个事件处理函数。例如，我们可以给某个链接添加一个 onclick 事件处理函数，并让这个处理函数所触发的 JavaScript 代码返回布尔值 true 或 false。这样一来，当这个链接被点击时，如果那段 JavaScript 代码返回的值是 true，onclick 事件处理函数就认为"这个链接被点击了"。反之，如果返回的值是 false，onclick 事件处理函数就认为"这个链接没有被点击"。
```html
    <a href="http://www.example.com" onclick="return false;">Click me</a>
```