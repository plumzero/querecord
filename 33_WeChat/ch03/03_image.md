
[参考](https://developers.weixin.qq.com/miniprogram/dev/component/image.html)

`image` 组件用来定义图片，类似于 HTML 中的 `<img>` 标签。

image 组件除了用来显示图片，还支持对图片进行裁剪或缩放，提供了 5 种缩放模式和 9 种裁剪模式。

常用属性如下:

| 属性 | 类型 | 默认值 | 必填 | 说明 |
|:----|:-----|:------|:-----|:-----|
| src | string | | 否 | 图片资源地址 |
| mode | string | scaleToFill | 否 | 图片裁剪、缩放模式 |
| lazy-load | boolean | false | 否 | 图片懒加载，只针对 page 与 scroll-view 下的 image 有效 |
| binderror | eventhandle | | 否 | 当错误发生时触发 |
| bindload | eventhandle | | 否 | 当图片载入完毕时触发 |

图片资源地址 `src` 可以是本地路径或 URL 地址。

