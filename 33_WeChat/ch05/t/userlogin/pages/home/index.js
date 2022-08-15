// pages/home/index.js
const app = getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    userInfo: {},
    hasUserInfo: false
  },

  credit: function() {
    wx.request({
      url: 'http://192.168.2.102:3000/credit',
      data: { token: app.globalData.token },
      success: res => {
        console.log(res.data)
      }
    })
  },

  getUserInfo: function(e) {
    wx.getUserProfile({
      desc: '展示用户信息',   // 声明获取用户个人信息后的用途
      success: res => {
        console.log(res.userInfo)
        // console.log(res)
        wx.setStorage({key: 'userInfo', data: res.userInfo})
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true   // 为 true 表示已经获得用户授权
        })
      }
    })
  },

  sendUserInfo: function() {
    var token = app.globalData.token
    wx.getUserProfile({
      desc: '将用户信息发给服务器',
      success: res => {
        wx.request({
          url: 'http://192.168.2.102:3000/userinfo?token=' + token,
          method: 'post',
          data: {
            rawData: res.rawData,
            signature: res.signature,
            encryptedData: res.encryptedData,
            iv: res.iv
          }
        })
      }
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    // 注释掉下面的代码，尝试手动获取数据
    if (app.globalData.userInfo) {
      this.setData({
        userInfo: app.globalData.userInfo,
        hasUserInfo: true
      })
    }
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