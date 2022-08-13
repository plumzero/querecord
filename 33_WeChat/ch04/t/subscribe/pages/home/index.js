// pages/home/index.js
const app = new getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },

  allowSubscribe: function() {
    if (!app.globalData.hasSubscribeMessage) {
      // 当用户在用户信息页面填写信息时，就询问用户是否允许订阅消息
      // 在这里的具体表现为在点击输入框时会弹出一个选择对话框，点击 '允许' 按钮后用户就可以使用订阅消息了
      wx.requestSubscribeMessage({
        tmplIds: ['UnSF_aMTiX4mBMFlTL7tio8O283jKMjS3VASgEUEiUE'], // 要订阅的模板
        success(res) {
          console.log(res)
          app.globalData.hasSubscribeMessage = res.errMsg.split(':')[1]
        }
      })
    }
  },

  formSubmit: function(e) {
    var name = e.detail.value.name
    var code = app.globalData.code
    console.log('发送信息: ', name, code)
    wx.request({
      url: 'http://192.168.2.102:8000/formsubmit',
      method: 'post',
      data: {
        name,
        code
      }
    })
    // 在此处可编写代码将 e.detail.value 提交到服务器

    wx.showToast({
      title: '提交成功',
      icon: 'success',
      duration: 1500
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  }
})