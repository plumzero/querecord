
[参考](https://developers.weixin.qq.com/miniprogram/dev/component/picker.html)

`picker` 组件是从底部弹起的滚动选择器，目前支持 5 种选择器，通过 `mode` 属性来区分，分别是:
- 普通选择器: mode="selector"
- 多列选择器: mode="multiSelector"
- 时间选择器: mode="time"
- 日期选择器: mode="date"
- 省市区选择器: mode="region"
默认是普通选择器。

示例如下:
```xml
  <picker range="{{array}}" value="{{index}}" bindchange="pickerChange">
    <view>当前选择: {{array[index]}}(点我修改)</view>
  </picker>
```
```js
  data: {
    array: ['HTML', 'CSS', 'JavaScript', 'Photoshop'],
    index: 1
  },
  pickerChange: function(e) {
    console.log('用户选择的值为: ', e.detail.value)
    this.setData({index: e.detail.value})
  }
```
上述代码中, `range` 属性表示显示在底部选择器的列表数组，数组中的每一个元素对应列表中的每一项。`value` 属性表示当前选择了 range 数组中的某个元素的下标，默认值为 0(下标从 0 开始)。`bindchange` 用于绑定 change 事件，该事件会在 value 改变时触发。

[示例工程](t/pickert)
