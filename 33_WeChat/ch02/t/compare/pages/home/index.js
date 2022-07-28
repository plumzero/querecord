// pages/home/index.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
      num1: 0,
      num2: 0,
      result: ''
  },

  num1change: function(e) {
    this.num1 = Number(e.detail.value)
    console.log('第1个数字为' + this.num1)
  },

  num2change: function(e) {
    this.num2 = Number(e.detail.value)
    console.log('第2个数字为' + this.num2)
  },

  change: function(e) {
    this[e.currentTarget.id] = Number(e.detail.value) // 利用了计算属性
  },

  change2: function(e) {
    console.log(e.target.dataset.id, '=>', e.detail.value)
    this[e.target.dataset.id] = Number(e.detail.value)
  },

  change3: function(e) {
    var data = {}
    data[e.target.dataset.id] = Number(e.detail.value)
    this.setData(data)
  },

  formCompare: function(e) {
    var str = '两数相等'
    var n1 = Number(e.detail.value.num1)
    var n2 = Number(e.detail.value.num2)
    if (n1 > n2) {
      str = '第 1 个数大'
    } else if (n1 < n2) {
      str = '第 2 个数大'
    }
    this.setData({result: str})
  },

  compare: function() {
    var str = '两数相等'
    if (this.num1 > this.num2) {
      str = '第 1 个数大'
    } else if (this.num1 < this.num2) {
      str = '第 2 个数大'
    }
    this.setData({result: str})
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    console.log('页面加载')
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {
    console.log('页面初次渲染完成')
    // wx.navigateTo({
    //   url: '/pages/test/index?name1=value1&name2=value2',
    // })
    var app = getApp()
    console.log(app.num)
    app.test()
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {
    console.log('页面显示')
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
    console.log('此时用户下拉触顶')
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {
    console.log('此时用户上拉触底')
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  },

  onPageScroll(options) {
    console.log('此时用户正在滚动页面')
    console.log('滚动距离:' + options.scrollTop)
  }
})