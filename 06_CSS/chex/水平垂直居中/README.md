

参考垂直居中的 `position` 实现，将 `top` 和 `left` 均设置为 50%，之后将 `margin-top` 和 `margin-left` 设置为子元素对应宽度和高度的一半，取负。

- [测试html](01.html)
- [测试css](01.css)

通过 flex 布局，利用 `justify-content` 和 `align-items` 分别设置水平和垂直方向上的居中。

- [测试html](02.html)
- [测试css](02.css)

将子元素的 `left`、`top`、`right` 和 `bottom` 的值设置为 0，此时子元素就会填充父元素的所有可用空间。再通过 `margin: auto` 自适应四周实现居中。

- [测试html](03.html)
- [测试css](03.css)


