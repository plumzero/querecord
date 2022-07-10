import { createApp } from 'vue'

import { createRouter, createWebHashHistory } from 'vue-router'

import App from './App.vue'

import UserCenter from './components/UserCenter.vue'
import UserSetting from './components/UserSetting.vue'
import CategoryT from './components/CategoryT.vue'
import NoUser from './components/NoUser.vue'
import FriendList from './components/FriendList.vue'

const app = createApp(App)

// 定义路由
const routes = [
    { path: '/user/:username', component: UserCenter,
      children: [
          {
              path: 'friends/:count', component: FriendList
          }
      ]
    },
    { path: '/user/:id(\\d+)', component: UserSetting },
    { path: '/category/:cat*', component: CategoryT },
    { path: '/user/:username?', component: NoUser }
]

// 创建路由对象
const router = createRouter({
    history: createWebHashHistory(),
    routes: routes
})

// 注册路由
app.use(router)

// 应用挂载
app.mount('#app')
