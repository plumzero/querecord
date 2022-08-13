// pages/map/map.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    latitude: 40.06021,
    longitude: 116.3433,
    markers: [{
      iconPath: '/images/navi.png',
      id: 0,
      latitude: 40.06021,
      longitude: 116.3433,
      width: 50,
      height: 50
    }
    ]
  },

  markertap: function() {
    wx.openLocation({
      latitude: this.data.latitude,
      longitude: this.data.longitude,
      name: 'xxx大酒店',
      address: '明市'
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