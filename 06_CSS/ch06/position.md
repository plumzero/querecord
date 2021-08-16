
`position` 属性的合法值有 `static`、`fixed`、`relative` 和 `absolute` 四种。

static 是 position 属性的默认值，意思是有关元素将按照它们在标记里出现的先后顺序出现在浏览器窗口里。

relative 的含义与 static 相似，区别是 postion 属性为 relative 的元素还可以通过应用 `float` 属性从文档的正常显示顺序里脱离出来。

设置为 absolute 可以将元素摆放到容纳它的"容器"的任何位置。这个容器要么是文档本身，要么是一个有着 `fixed` 或 `absolute` 属性的父元素。要摆放的元素在原始标记里出现的位置与它的显示位置无关，因为它的显示位置由 `top`、`left`、`right` 和 `bottom` 等属性决定。可以使用像素或百分比作为单位设置这些属性的值。
