
[参考](https://developers.weixin.qq.com/miniprogram/dev/component/scroll-view.html)

`scroll-view` 组件用于实现可滚动视图区域。

该组件的常用属性如下:

| 属性 | 类型 | 默认值 | 必填 | 说明 |
|:----|:-----|:-----|:------|:-----|
| scroll-x | boolean | false | 否 | 允许横向滚动 |
| scroll-y | boolean | false | 否 | 允许纵向滚动 |
| scroll-top | number/string | | 否 | 设置竖向滚动条位置 |
| scroll-left | number/string | | 否 | 设置横向滚动条位置 |
| bindscrolltoupper | eventhandle | | 否 | 滚动到顶部/左边时触发 |
| bindscrolltolower | eventhandle | | 否 | 滚动到底部/右边时触发 |
| scroll-with-animation | boolean | false | 否 | 在设置滚动条位置时使用动画过渡 |
| scroll-into-view | string | | 否 | 设置哪个方向可滚动，则在哪个方向滚动到该元素。值应为某子元素id(不能以数字开头) |
| bindscroll | eventhandle |  | 否 | 滚动时触发 |

> 注意，纵向滚动需要在样式中为 `<scroll-view>` 设置一个固定高度，否则它会被子元素撑大。

### 关于项目

由于 content 区域的可显示高度是有限的，而'音乐推荐'中的实际内容可能会超过显示区域的高度，因此在 `<swiper-item>` 标签内使用 `<scroll-view>` 组件，用于实现内容的上下滚动。
