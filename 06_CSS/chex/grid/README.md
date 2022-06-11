
grid 是二维布局方式，可以同时控制行和列的排布和对齐方式。

grid 由水平线和垂直线构成，两条水平线之间的区域称为 `行轨道`，两条垂直线之间的区域称为 `列轨道`。

通过 `display: grid` 可以开启该布局，这样容器的直接子元素就会成为 grid 布局的元素。

可以通过 `grid-template-columns` 属性指定每个子元素的固定宽度:
```css
	display: grid;
	grid-template-columns: 100px 100px 100px;
```
上面的样式表示子元素为三列布局，每列宽度 100px。

也可以通过 `grid-template-columns: 1fr 1fr 1fr` 指定浮动宽度。

通过 `column-gap` 属性可以设置列间距，通过 `row-gap` 属性可以设置行间距，或者通过 `gap` 属性统一设置。

- [测试html](01.html)
- [测试css](01.css)

可以使用 `grid-template-areas` 排列元素。

- [测试html](02.html)
- [测试css](02.css)

grid 对方方式与 flex 布局方式类似，有水平方向上的`行轴`和垂直方向上的`块轴`。

在垂直方向上对齐子元素可以使用 `align-items` 属性，其可取值及含义如下:
- `center`: 居中对齐
- `end`: 靠下对齐

在水平方向上对齐子元素可以使用 `justify-items` 属性，其可取值及含义如下:
- `center`: 居中对齐
- `end`: 靠右对齐
- `space-between`: 两端对齐

- [测试html](03.html)
- [测试css](03.css)


如果行轨道和列轨道的尺寸小于父容器元素，还可以对轨道进行对齐。

在垂直方向上使用 `align-content` 属性，其可取值及含义如下:
- `center`: 居中对齐
- `end`: 靠下对齐

在水平方向上使用 `justify-content` 属性，其可取值及含义如下:
- `center`: 居中对齐
- `end`: 靠右对齐
- `space-between`: 两端对齐
