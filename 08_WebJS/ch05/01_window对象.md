
JavaScript 的 window 对象，即窗口对象，它处在文档对象模型的层次的最顶层。window 对象为 web 浏览器所有内容的容器，只要打开浏览器窗口，即使没有任何内容，浏览器也会在内存中创建一个 window 对象。每打开一个浏览器窗口都对应 JavaScript 脚本程序中的一个 window 对象。

window 对象和其他对象一样提供了一些属性和方法对窗口的内容进行控制，利用这些属性和方法，再配合一定的事件处理机制，可以实现很多的功能。


### window 对象的属性

| 常用属性 | 意义 |
|:--------|:-----|
| name    | 窗口的名字，窗口名称可通过 `window.open()` 方法指定，也可以在 `<frame>` 标记中使用 name 属性指定 |
| closed  | 判断窗口是否已经被关闭，返回布尔值 |
| length  | 窗口内的框架个数 |
| opener  | 代表使用 open 打开当前窗口的父窗口 |
| self    | 当前窗口，指对本身窗口的引用 |
| window  | 当前窗口，与 self 属性意义相同 |
| top     | 当前框架的最顶层窗口 |
| defaultstatus | 缺省的状态栏信息 |
| status  | 状态栏的信息 |
| innerHeight/innerWidth | 网页内容区的高度与宽度 |
| outerHeight/outerWidth | 网页边界的高度与宽度，以像素为单位 |
| pageXOffset/pageYOffset | 网页左上角的坐标值，整数型只读值，指定当前文档向右、向下移动的多少像素 |
| scrollbars | 浏览器的滚动条 |
| toolbar | 浏览器的工具栏 |
| menubar | 浏览器的菜单栏 |
| locationbar | 浏览器的地址栏 |
| document | 只读，引用当前窗口活框架包含 document 对象 |
| frames | 记录窗口中包含的框架 |
| history | 只读，引用 history 对象 |
| location | 引用 location 对象 |


### window 对象的方法

| 方法 | 意义  |
|:-----|:------|
| open() | `open(URL,窗口名[,窗口规格])` 打开一个新窗口。返回值为窗口名 |
| close() | 关闭窗口 |
| clearInterval(定时器名) | 清除定时器，无返回值 |
| clearTimeout(超时名)    | 清除先前设置的超时，无返回值 |
| setTimeout(表达式, n毫秒数) | 等待 n 毫秒后，运行表达式 |
| setInterval(表达式, n毫秒数) | 每隔 n 毫秒，运行表达式 |
| moveBy(水平点数, 垂直点数) | 正值为窗口往右下方移动，负值相反 |
| moveTo(x, y) | 窗口移动 x, y 坐标处(左上角) |
| resizeBy(水平点数, 垂直点数) | 调整窗口大小，往右下方向增加 |
| resizeTo(w, h) | 调整窗口大小，宽w, 高h |
| focus() | 得到焦点 |
| blur()  | 失去焦点 |
| home()  | 类似浏览器工具栏的主页 |
| stop()  | 类似浏览器工具栏的停止 |
| back()  | 类似浏览器工具栏的后退 |
| forward() | 类似浏览器工具栏的前进 |
| alert(字符串) | 弹出警告信息 |
| confirm(字符串) | 弹出警告信息，增加 ok, cancel 按钮，根据用户单击的按钮，返回 true 与 false |
| prompt(提示, 默认值) | 弹出对话框，返回用户输入的文本 | 


### 在 JavaScript 中引用 window 对象属性和方法

Window 对象的属性和方法在 JavaScript 中的引用与其他对象的引用方法一样，通过对对象名称的引用，来明确对象的属性、方法，具体如下:
```js
    window.属性
    window.方法
```

另外可以通过  self 属性来引用当前窗口的属性和方法，使用它引用 window 对象与使用 window 对象完全一样。引用方式同 window 对象。

在含有多个窗口的脚本程序中，使用 self 引用当前窗口可以确保准确的调用当前窗口的属性和方法。

在 JavaScript 中，还可以不使用标识符 window 和 self，直接引用 window 对象的属性和方法:close() 和 open() 关闭和打开窗口，执行效果是一样的。
