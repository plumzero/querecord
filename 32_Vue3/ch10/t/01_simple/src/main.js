import { createApp } from 'vue'

import { createRouter, createWebHashHistory } from 'vue-router'

import App from './App.vue'

import Demo1 from './components/Demo1Name.vue'
import Demo2 from './components/Demo2Name.vue'

const app = createApp(App)

// 定义路由
const routes = [
    { path: '/demo1', component: Demo1 },
    { path: '/demo2', component: Demo2 }
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
