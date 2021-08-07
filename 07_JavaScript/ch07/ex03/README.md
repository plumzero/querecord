
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

