
### 过渡动画

过渡可以实现元素不同状态间的平滑过渡(补间动画)，经常用来制作动画效果。

过渡属性有 4 个，具体如下:

| 属性 | 说明 |
|:----|:------|
| transition-property | 规定应用过渡的 CSS 属性的名称，默认为 all，即所有属性都应用过渡动画 |
| transition-duration | 定义过渡效果花费时间，默认为 0 秒，表示没有动画效果。如果设置为 5 秒，表示 5 秒内完成过渡动画效果 |
| transition-timing-function | 规定过渡效果的时间曲线 |
| transition-delay | 规定过渡效果何时开始，默认为 0 表示立即开始。如果设置为 5 秒，表示 5 秒后开始过渡动画 |

`transition-timing-function` 的属性值及意义如下:

| 属性值     | 意义 |
|:----------|:-----|
| linear    | 规定以相同速度开始至结束的过渡效果 |
| ease      | 规定慢速开始，然后变快，最后慢速结束的效果。这也是默认效果 |
| ease-in   | 规定以慢速开始的过渡效果 |
| ease-out  | 规定以慢速结束的过渡效果 |
| ease-in-out | 规定以慢速开始和结束的过渡效果 |

[过渡动画示例](t/03_transition.html)


### animation 动画

animation 动画可通过设置多个节点来精确控制一个或一组动画，常用来实现复杂的动画效果。

创建 animation 动画，首先要使用 `@keyframes` 定义关键帧，其语法格式如下:
```css
    @keyframes animationname {keyframes-selector {css-styles;}}
```
* 其中 `animationname` 是动画名称，也是必须使用的。
* `keyframes-selector`表示动画持续的百分比，也是必须使用的。合法值是 0%~100%，也可以是 from 和 to，from 表示 0%，to 表示 100% 。
* `css-styles` 就是一个或多个 CSS 样式。

animation 属性有以下几个:

| 属性 | 说明 |
|:----|:------|
| animation-name | 指定要绑定的动画名称 |
| animation-duration | 定义动画完成一个周期的秒数 |
| animation-timing-function | 指定动画将如何完成一个周期 |
| animation-delay | 规定动画效果何时开始，默认为 0 表示立即开始。如果设置为 5 秒，表示 5 秒后开始动画 |
| animation-iteration-count | 定义动画应该播放多少次，默认值为 1，即播放一次。如果为 infinite 表示一直播放 |
| animation-direction | 定义是否循环交替反向播放动画。注意，如果动画只播放一次，则此属性将不起作用 |

`animation-timing-function` 的属性值及意义如下:

| 属性值     | 意义 |
|:----------|:-----|
| linear    | 规定以相同速度开始至结束的动画效果 |
| ease      | 规定慢速开始，然后变快，最后慢速结束的效果。这也是默认效果 |
| ease-in   | 规定以慢速开始的动画效果 |
| ease-out  | 规定以慢速结束的动画效果 |
| ease-in-out | 规定以慢速开始和结束的动画效果 |

`animation-direction` 的属性值及意义如下:

| 属性值     | 意义 |
|:----------|:-----|
| normal    | 默认值，动画按正常播放 |
| reverse   | 动画反向播放 |
| alternate | 动画在奇数次(1、3、5...)正向播放，在偶数次(2、4、6...)反向播放 |
| alternate-reverse | 动画在奇数次(1、3、5...)反向播放，在偶数次(2、4、6...)正向播放 |

[animation动画示例](t/03_animation.html)
