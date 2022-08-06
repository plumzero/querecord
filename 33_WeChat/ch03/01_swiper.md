
[参考](https://developers.weixin.qq.com/miniprogram/dev/component/swiper.html)

`swiper` 是滑块视图容器，其中只可放置 `swiper-item` 组件，经常用于实现轮播图。
```xml
  <swiper>
    <swiper-item style="background:#ccc">0</swiper-item>
    <swiper-item style="background:#ddd">1</swiper-item>
    <swiper-item style="background:#eee">2</swiper-item>
  </swiper>
```
在 `<swiper-item>` 标签中，如果放入 image 组件，就实现了轮播图的效果；如果放入一块页面内容，就实现了标签页切换的效果。

swiper 组件的一些常用属性如下:

| 属性 | 类型 | 默认值 | 必填 | 说明 |
|:----|:-----|:------|:-----|:-----|
| indicator-dots | boolean | false | 否 | 是否显示面板指示点 |
| indicator-color | color | rgba(0, 0, 0, .3) | 否 | 指示点颜色 |
| indicator-active-color | color | #000000 | 否 | 当前选中的指示点颜色 |
| autoplay | boolean | false | 否 | 是否自动切换 |
| current | number | 0 | 否 | 当前所在滑块的 index |
| interval | number | 5000 | 否 | 自动切换时间间隔(ms) |
| duration | number | 500 | 否 | 滑动动画时长 |
| circular | boolean | false | 否 | 是否采用衔接滑动 |
| vertical | boolean | false | 否 | 滑动方向是否为纵向 |
| bindchange | eventhandle | | 否 | current 改变时会触发 change 事件，event.detail = {current,source} |

### 关于项目

在该小程序中，切换标签页有两种方式，一种是直接滑动 content 区域，另一种是通过单击 tab 区域中的某一个 tab-item 切换到对应的标签页。

针对第二种的实现，修改 tab 视图代码:
```xml
  <view class="tab-item" bindtap="changeItem" data-item="0">音乐推荐</view>
  <view class="tab-item" bindtap="changeItem" data-item="1">播放器</view>
  <view class="tab-item" bindtap="changeItem" data-item="2">播放列表</view>
```
'data-item' 关联到 swiper 组件中对应的 swiper-item 的索引。

接下来的思路就是通过 bindtap 事件绑定的函数修改 data 中的变量，让它反映到 swiper 的 current 属性上，实现标签页的切换。

在切换标签页后，还需要改变当前标签页对应的 tab-item 的样式，以区别于其他未处于活跃状态的标签页。可以增加一个变量 'tab' 来变化活跃标签页的样式。