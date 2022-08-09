
从其他地方获取的 data 数据有时可能不适合直接显示到页面中，这时需要对数据进行转换后才能显示。针对这种情况，可以在 WXML 文件中通过 `WXS` 嵌入代码。

比如对于一个 unix 时间戳，需要将其转换为钟表时间进行显示。具体实现如下:

在 wxml 文件中，通过 `<wxs>` 标签定义一个函数，用于将时间戳转换为钟表时间:
```xml
  <wxs module="formatData">
    module.exports = function(timestamp) {
      var date = getDate(timestamp)
      var y = date.getFullYear()
      var m = date.getMonth() + 1
      var d = date.getDate()
      var h = date.getHours()
      var i = date.getMinutes()
      var s = date.getSeconds()
      return y + '-' + m + '-' + d + ' ' + h + ':' + i + ':' + s
    }
  </wxs>
```
在上面的代码中，`<wxs>` 标签用于在 WXML 中嵌入 WXS 代码，属性 `module` 表示模块名称。通过 `exports` 可以将其赋值给一个对象或函数。 上面将其赋值给一个 'formatData' 函数；如果赋值的是一个对象，则使用 'formatData.属性名' 来使用。

使用示例如下:
```xml
  <view class="video-time">时间: {{formatData(item.create_time)}}</view>
```

> 注: 由于 WXS 中不支持 'new Date()'，因此使用 'getDate()' 函数代替。
