// pages/index/index.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    isPlayingMusic: false,
    bgm: null,
    music_url: 'http://192.168.0.105:3000/你的眼神.mp3',
    music_coverImgUrl: '1234'
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
    this.bgm = wx.getBackgroundAudioManager()
    this.bgm.title = 'marry me'
    this.bgm.epname = 'wedding'
    this.bgm.singer = 'singer'
    this.bgm.coverImgUrl = this.music_coverImgUrl
    this.bgm.onCanplay(() => {
      this.bgm.pause()
    })
    this.bgm.src = this.music_url != undefined ? this.music_url : 'http://192.168.0.105:3000/你的眼神.mp3'
  },

  play: function(e) {
    if (this.data.isPlayingMusic) {
      this.bgm.pause()
    } else {
      this.bgm.play()
    }
    this.setData({
      isPlayingMusic: !this.data.isPlayingMusic
    })
  },

  callGroom: function() {
    wx.makePhoneCall({ phoneNumber: '13700000000' })
  },

  callBride: function() {
    wx.makePhoneCall({ phoneNumber: '15600000000' })
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