
### 实现功能

* 向文档中添加标记，从而达到动态改变网页结构目的。


### 学习目标

* 了解 document.write 的坏处
* innerHTML 的使用
* 了解 DOM 方法与文档的作用原理
* 了解常用的节点操作方法


### innerHTML 属性

`innerHTML` 和 `document.write()` 都是 HTML 文档的专有属性和方法，不能用于其他标记语言文档(如 MIME 类型是 application/xhtml+xml 的 XHTML 文档)。

innerHTML 属性比 document.write() 方法更值得推荐使用。innerHTML 属性可以用来读、写某给定元素里的 HTML 内容。在你需要把一大段 HTML 内容插入网页时，innerHTML 属性更适用。

innerHTML 属性不会返回任何对刚插入的内容的引用。任何时候，标准 DOM 都可以替代 innerHTML 来达到更精细的操作效果。

### DOM 方法与文档的作用原理

DOM 是文档的表示。DOM 所包含的信息与文档里的信息一一对应。DOM 不仅可以获取文档的内容，还可以更新文档的内容。如果你改变了 DOM 节点树，文档在浏览器里的呈现效果就会发生变化。比如用 setAttribute 方法改变了 DOM 节点树上的某个属性节点后，相关文档在浏览器里的呈现就会发生相应的变化。不过，setAttribute 方法并未改变文档的物理内容，只有在用浏览器打开那份文档时才能看到文档呈现效果的变化。这是因为浏览器实际显示的是那棵 DOM 节点树。在浏览器看来，DOM 节树才是文档。

所以通过 DOM 创建标记其实就是在改变 DOM 节点树。在 DOM 看来，一个文档就是一棵节点树。如果你想在节点树上添加内容，就必须插入新的点。如果你想添加一些标记到文档，就必须插入元素节点。

### createElement 方法

创建一个元素节点。
```js
    var para = document.createElement("p");
```
变量 para 现在包含着一个指向刚创建出来的那个 p 元素的引用。不过它还不是任何一棵 DOM 节点树的组成部分，只是游荡在 JavaScript 世界里的一个孤儿。它这种情况称为文档碎片(document fragment)，还无法显示在浏览器的窗口画面里。不过，它已经像任何其他的节点那样有了自己的 DOM 属性。

### appendChild 方法

子节点插入到父节点中。
```js
    parent.appendChild(child);
```

### createTextNode 方法

创建一个文本节点。
```js
    var txt = document.createTextNode("Hello world");
```
变量 txt 现在包含指向新创建的那个文本节点的引用。这个节点也是未被插入任何一个文档的节点树下。

### insertBefore 方法

把一个新元素插入到一个现有元素的前面。
```js
    parentElement.insertBefore(newElement, targetElement);
```
newElement 为想插入的新元素，targetElement 为想把新元素插入到那个之前的目标元素，parentElement 为目标元素的父元素。

### 自定义 insertAfter 方法

DOM 本身并未提供 insertAfter 方法，这里可以编写一个:
```js
    function insertAfter(newElement, targetElement) {
        var parent = targetElement.parentNode;
        if (parent.lastChild == targetElement) {
            parent.appendChild(newElement);
        } else {
            parent.insertBefore(newElement, targetElement.nextSibling);
        }
    }
```
