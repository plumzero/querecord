
在 JavaScript 中，一个浏览器窗口就是一个 window 对象。

简单来说，JavaScript 会把一个窗口看成一个对象，这样我们就可以用这个对象的属性和方法来操作这个窗口。实际上，我们每次打开一个页面时，浏览器都会自动为这个页面创建一个 window 对象。

window 对象存放了这个页面的所有信息，为了更好地分类处理这些信息，window 对象下面又分为很多对象。window 的子对象如下:

| 子对象  | 说明  |
|:-------|:------|
| document | 文档对象，用于操作页面元素 |
| location | 地址对象，用于操作 URL 地址 |
| navigator | 浏览器对象，用于获取浏览器版本信息 |
| history | 历史对象，用于操作浏览历史 |
| screen | 屏幕对象，用于操作屏幕宽度高度 |

document 对象也仅是 window 对象下的一个子对象。因为一个窗口不仅仅包括 HTML 文档，还包括浏览器信息、浏览历史和浏览地址等。

window 对象及下面的 location、navigator 等子对象，由于都是操作浏览器窗口的，又称之为"BOM"，也就是浏览器对象模型。

window 对象常用方法:

|   方法   | 说明 |
|:---------|:-----|
| alert()  | 提示对话框 |
| confirm() | 判断对话框 |
| prompt() | 输入对话框 |
| open()   | 打开窗口 |
| close()  | 关闭窗口 |
| setTimeout() | 开启"一次性"定时器 |
| clearTimeout() | 关闭"一次性"定时器 |
| setInterval() | 开启"重复性"定时器 |
| clearInterval() | 关闭"重复性"定时器 |

对于 window 对象来说，无论是它的属性还是方法，都可以省略 window 前缀。例如 alert() 就是 window.alert() 的简写，而 window.open() 也可以简写成 open()。而 document.getElementById() 是 window.document.getElementById() 的简写。
