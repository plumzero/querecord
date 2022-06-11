
说明:
- block 元素默认的宽度是父容器的可用空间。
- `text-align` 属性只对文本文字和 img 标签有效。

这里将 block 元素的宽度按不足 100% 设置，进行测试。

为父容器元素设置 `text-align: center;` 样式，`inline` 和 `inline-block` 会水平居中。它们整个元素都被理解为与文字一样，所以可以通过父容器的 text-align 设定将它们水平居中对齐。

而 block 元素由于没有设定 text-align 属性，所以它继承了父元素的 text-align 设定，只能对文字居中，而元素本身并未被水平居中。

如果需要将整个 block 元素在页面内水平居中，可以将 block 元素的 `margin-left` 和 `margin-right` 设成 auto 来实现。
```css
	margin: 0 auto;		// 上下外边距为 0， 左右自适应
```

- [测试html](01.html)
- [测试css](01.css)

通过 flex 布局，通过 `justify-content: center` 横轴方向的水平居中。

- [测试html](02.html)
- [测试css](02.css)
