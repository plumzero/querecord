
flex 是一维布局方式。默认情况下其直接子元素就会按行排列。

在行模式下，有一条水平方向的主轴和一条垂直方向的交叉轴。子元素会从父容器左上角开始(即主轴最左边、交叉轴最上边)，从左到右依次排列。

但是主轴未必一定是水平方向，交叉轴也未必是垂直方向，二者可以通过 `flex-direction: column` 实现角色互换。

改变主轴方向上的布局使用 `justify-content` 属性，其可取值及含义如下:
- `flex-end`: 靠右对齐
- `center`: 居中对齐
- `space-evenly`: 平分空间
- `space-between`: 两端对齐

- [测试html](01.html)
- [测试css](01.css)

改变交叉轴方向上的布局使用 `align-items` 属性，其可取值及含义如下:
- `flex-end`: 靠下对齐
- `center`: 居中对齐

align-items 属性常与 `flex-direction: column` 结合使用。

- [测试html](02.html)
- [测试css](02.css)

可以通过为每个子元素设置不同的 `flex` 属性值来调整各子元素的空间占比。

- [测试html](03.html)
- [测试css](03.css)

由于 flex 会对其子元素进行一维布局，所以即便其子元素是 block 元素，也可以不用为该子元素设置 `display: inline-block` 属性。
