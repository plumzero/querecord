
DOM 遍历可以简单理解为"查找元素"。在 JavaScript 中，DOM 遍历可以分为以下三种情况:
* 查找父元素
* 查找子元素
* 查找兄弟元素

### 查找父元素

在 JavaScript 中，可以使用 `parentNode` 属性来获得某个元素的父元素。
```js
    node.parentNode
```

[查找父元素示例](t/04_parentNode.html)


### 查找子元素

在 JavaScript 中，可以使用以下两组方式来获得父元素中的所有子元素或某个子元素。
* 方式一: childNodes firstChild lastChild
* 方式二: children firstElementChild lastElementChild
其中，`childNodes` 获取的是所有的子节点。注意，这个子节点是包括元素节点以及文本节点的，而 `children` 获取的是所有的元素节点，不包括文本节点。

[childNodes与children的比较示例](t/04_childNodes_children.html)

[方式一删除元素子节点](t/04_removeChild_1.html)

[方式二删除元素子节点](t/04_removeChild_2.html)


### 查找兄弟元素

在 JavaScript 中，可以使用以下两组方式来获得兄弟元素。
* previousSibling nextSibling
* previousElementSibling nextElementSibling
`previousSibling` 查找前一个兄弟节点，`nextSibling` 查找后一个兄弟节点。`previousElementSibling` 查找前一个兄弟元素节点，`nextElementSibling` 查找后一个兄弟元素节点。

跟查找子元素的两组方式一样，第一组查找出来的可能是文本节点(一般是空白节点)。

[删除某个兄弟节点](t/04_removeSibling.html)
