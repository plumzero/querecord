
[参考](https://developers.weixin.qq.com/miniprogram/dev/api/media/audio/InnerAudioContext.html)

微信小程序提供了播放音频的 API。在使用音频 API 时，需要通过如下代码创建一个 `InnerAudioContext` 实例。
```js
  var audioCtx = new wx.createInnerAudioContext()
```
在上述代码中，audioCtx 就是一个 InnerAudioContext 实例，也就是一个对象。利用这个对象的属性和方法可以完成具体的工作。

InnerAudioContext 实例常用属性如下:

| 属性 | 类型 | 默认值 | 说明 |
|:----|:-----|:------|:-----|
| src | string | | 音频资源的地址，用于直接播放 |
| startTime | number | 0 | 开始播放的位置(s) |
| autoplay | boolean | false | 是否自动开始播放 |
| loop | boolean | false | 是否循环播放 |
| volume | number | 1 | 音量。范围 0~1 |
| duration | number | | 当前音频的长度(单位s)。只有在当前有合法的 src 时返回(只读) |
| currentTime | number | | 当前音频的播放位置(单位 s)。只有在当前有合法的 src 时返回，时间保留小数点后 6 位(只读)|
| paused | boolean | | 当前是否暂停或停止状态(只读) |

InnerAudioContext 实例常用方法如下:

| 名称 | 说明 |
|:----|:-----|
| play() | 播放 |
| pause() | 暂停(暂停后的音频再播放会从暂停处开始播放) |
| stop() | 停止(停止后的音频再播放会从头开始播放) |
| seek() | 跳转到指定位置 |
| destroy() | 销毁当前实例 |
| onCanplay(function cb) | 监听音频进入可以播放状态的事件。但不保证后面可以流畅播放 |
| onPlay(function cb) | 监听音频播放事件 |
| onPause(function cb) | 监听音频暂停事件 |
| onStop(function cb) | 监听音频停止事件 |
| onEnded(function cb) | 监听音频自然播放至结束的事件 |
| onSeeked(function cb) | 监听音频完成跳转操作的事件 |
| onTimeUpdate(function cb) | 监听音频播放进度更新事件 |
| onError(function cb) | 监听音频播放错误事件 |

示例代码:
```js
  onReady: function() {
    var audioCtx = wx.createInnerAudioContext()
    // 设置音频资源地址
    audioCtx.src = 'http://....../xx.mp3'
    // 当开始播放时，输出调试信息
    audioCtx.onPlay(function() {
      console.log('开始播放')
    })
    // 当发生错误时，输出调试信息
    audioCtx.onError(function(res) {
      console.log(res.errMsg)   // 错误信息
      console.log(res.errCode)  // 错误码
    })
    // 开始播放
    audioCtx.play()
  },
```

在小程序中，还有一种专门用于播放背景音频的 `wx.getBackgroundAudioManager()` 接口，其特点在于小程序切入后台时，如果音频处于播放状态，可以继续播放。

为了实现这个效果，需要先在 app.json 中添加如下配置，添加后在开发版中会直接生效，正式版还需通过审核。
```json
  "requiredBackgroundModes": ["audio"],
```

[更多...](https://developers.weixin.qq.com/miniprogram/dev/api/media/background-audio/BackgroundAudioManager.html)
