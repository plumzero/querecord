// app.js
App({
  onLaunch() {
    this.checkLogin(res => {
      console.log('is_login:', res.is_login)
      if (!res.is_login) {
        this.login()
      }
    })
    this.globalData.userInfo = wx.getStorageSync('userInfo')
    console.log(this.globalData.userInfo)
  },

  login: function() {
    wx.login({
      success: res => {
        console.log('login code: ' + res.code)
        wx.request({
          url: 'http://192.168.2.102:3000/login',
          method: 'post',
          data: { code: res.code },
          success: res => {
            console.log('token: ' + res.data.token)
            // 将 token 保存为公共数据(用于在多页面中访问)
            this.globalData.token = res.data.token
            // 将 token 保存到数据缓存(下次打开小程序无需重新获取 token)
            wx.setStorage({key:'token', data:res.data.token})
          }
        })
      }
    })
  },

  checkLogin: function(callback) {
    var token = this.globalData.token
    if (!token) {
      token = wx.getStorageSync('token')
      if (token) {
        this.globalData.token = token
      } else {
        callback({is_login: false})
        return
      }
    }
    wx.request({
      url: 'http://192.168.2.102:3000/checkLogin',
      data: { token: token },
      success: res => {
        callback({is_login: res.data.is_login})
      }
    })
  },

  globalData: {
    userInfo: null,
    token: null
  }
})
