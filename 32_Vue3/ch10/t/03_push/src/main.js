import { createApp } from 'vue'

import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import { createRouter, createWebHashHistory } from 'vue-router'

import App from './App.vue'

import UserCenter from './components/UserCenter.vue'

const app = createApp(App)

const routes = [
    { 
        path: '/user/:username?',
        name: 'user',
        component: UserCenter
    },
    {
        path: '/userx/:username?',
        name: 'userx',
        component: UserCenter
    }
]

const router = createRouter({
    history: createWebHashHistory(),
    routes: routes
})

app.use(ElementPlus)
app.use(router)

// 应用挂载
app.mount('#app')