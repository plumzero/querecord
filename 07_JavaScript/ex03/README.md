
### 实现功能

* 向文档中添加标记，从而达到动态改变网页结构目的。


### 学习目标

* 了解 document.write 的坏处
* innerHTML 的使用
* 了解 DOM 方法与文档的作用原理


### innerHTML 属性

`innerHTML` 和 `document.write()` 都是 HTML 文档的专有属性和方法，不能用于其他标记语言文档(如 MIME 类型是 application/xhtml+xml 的 XHTML 文档)。

innerHTML 属性比 document.write() 方法更值得推荐使用。innerHTML 属性可以用来读、写某给定元素里的 HTML 内容。在你需要把一大段 HTML 内容插入网页时，innerHTML 属性更适用。

innerHTML 属性不会返回任何对刚插入的内容的引用。任何时候，标准 DOM 都可以替代 innerHTML 来达到更精细的操作效果。

### DOM 方法与文档的作用原理

DOM 是文档的表示。DOM 所包含的信息与文档里的信息一一对应。DOM 不仅可以获取文档的内容，还可以更新文档的内容。如果你改变了 DOM 节点树，文档在浏览器里的呈现效果就会发生变化。比如用 setAttribute 方法改变了 DOM 节点树上的某个属性节点后，相关文档在浏览器里的呈现就会发生相应的变化。不过，setAttribute 方法并未改变文档的物理内容，只有在用浏览器打开那份文档时才能看到文档呈现效果的变化。这是因为浏览器实际显示的是那棵 DOM 节点树。在浏览器看来，DOM 节树才是文档。

所以通过 DOM 创建标记其实就是在改变 DOM 节点树。在 DOM 看来，一个文档就是一棵节点树。如果你想在节点树上添加内容，就必须插入新的点。如果你想添加一些标记到文档，就必须插入元素节点。

相关方法

| 方法 | 说明 |
|:-----|:----|
| createElement | 创建元素节点 |
| appendChild | 将某节点追加到另一节点 |
| createTextNode | 创建文本节点 |
| insertBefore | 在已有元素前插入一个新元素 |

