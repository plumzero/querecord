import { createApp } from 'vue'

import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import { createRouter, createWebHashHistory } from 'vue-router'

import App from './App.vue'

import UserCenter from './components/UserCenter.vue'
import UserSetting from './components/UserSetting.vue'

const app = createApp(App)

const routes = [
    { 
        path: '/user/:username/:id',
        components: {
            topBar: UserCenter,
            main: UserSetting,
        }
    }
]

const router = createRouter({
    history: createWebHashHistory(),
    routes: routes
})

app.use(ElementPlus)
app.use(router)

app.mount('#app')
