import { createApp } from 'vue'

import { createRouter, createWebHashHistory } from 'vue-router'

import App from './App.vue'

import UserAbout from './components/UserAbout.vue'

const app = createApp(App)

// 定义路由
const routes = [
    { path: '/user/:username/:id', component: UserAbout }
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
