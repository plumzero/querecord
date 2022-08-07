// index.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    item: 0,
    tab: 0,
    playlist: [{
      id: 1, title: '你的眼神', singer: '蔡琴', src: 'http://192.168.0.105:3000/你的眼神.mp3', coverImgUrl: '/images/cover.jpg',
      id: 2, title: '你会不会', singer: '陈奕迅', src: 'http://192.168.0.105:3000/你会不会.mp3', coverImgUrl: '/images/cover.jpg'
    }],
    state: 'paused',    // 播放状态: paused running
    playIndex: 0,       // 正播放曲目的索引
    play: {             // 正播放曲目的信息
      currentTime: '00:00', // 正播放时长
      duration: '00:00',    // 总时长
      percent: 0,           // 播放进度
      title: '',
      singer: '',
      coverImgUrl: '/images/cover.jpg'
    },
    audioCtx: null

  },

  changeItem: function(e) {
    this.setData({
      item: e.target.dataset.item
    })
  },

  changeTab: function(e) {
    this.setData({
      tab: e.detail.current
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    console.log("test options:", options)
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {
    this.audioCtx = wx.createInnerAudioContext()
    this.setMusic(0)  // 默认选择第一曲
    var that = this
    // 播放失败检测
    this.audioCtx.onError(function() {
      console.log('播放失败: ' + that.audioCtx.src)
    })
    // 播放完成自动换下一曲
    this.audioCtx.onEnded(function() {
      that.next()
    })
    // 自动更新播放进度
    this.audioCtx.onPlay(function() {})
    this.audioCtx.onTimeUpdate(function() {
      that.setData({
        'play.duration': formatTime(that.audioCtx.duration),
        'play.currentTime': formatTime(that.audioCtx.currentTime),
        'play.percent': that.audioCtx.currentTime / that.audioCtx.duration * 100
      })
    })
    // 格式化时间
    function formatTime(time) {
      var minute = Math.floor(time / 60) % 60
      var second = Math.floor(time) % 60
      return (minute < 10 ? '0' + minute : minute) + ':' + (second < 10 ? '0' + second : second)
    }
  },

  sliderChange: function(e) {
    var second = e.detail.value * this.audioCtx.duration / 100
    this.audioCtx.seek(second)
  },

  change: function(e) {
    this.setMusic(e.currentTarget.dataset.index)
    this.play()
  },

  setMusic: function(index) {
    var music = this.data.playlist[index]
    this.audioCtx.src = music.src
    this.setData({
      playIndex: index,
      'play.title': music.title,
      'play.singer': music.singer,
      'play.coverImgUrl': music.coverImgUrl,
      'play.currentTime': '00:00',
      'play.duration': '00:00',
      'play.percent': 0
    })
  },

  play: function() {
    this.audioCtx.play()
    this.setData({state: 'running'})
  },

  pause: function() {
    this.audioCtx.pause()
    this.setData({state: 'paused'})
  },

  next: function() {
    var index = this.data.playIndex >= this.data.playlist.length - 1 ? 0 : this.data.playIndex + 1
    this.setMusic(index)
    if (this.data.state === 'running') {
      this.play()
    }
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