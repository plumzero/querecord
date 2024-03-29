// app.js
App({
  // 生命周期回调 —— 监听小程序初始化
  // 小程序初始化完成时触发(全局只触发一次)
  onLaunch(options) {
    console.log('onLaunch执行')
    console.log(options)
  },
  // 生命周期回调 —— 监听小程序显示
  // 小程序启动，或从后台进入前台显示时触发
  onShow(options) {
    console.log('onShow执行')
    console.log(options)
  },
  // 生命周期回调 —— 监听小程序隐藏
  // 小程序从前台进入后台时触发
  onHide() {
    console.log('onHide执行')
  },
  // 错误监听函数
  // 小程序发生脚本错误，或者 API 调用失败时触发
  onError(error) {
    console.log('onError执行')
    console.log(error)
  },
  // 页面不存在监听函数
  onPageNotFound(options) {
    console.log('onPageNotFound执行')
    console.log(options)
  },
  num: 123,
  test: function() {
    console.log('test')
  }
})
