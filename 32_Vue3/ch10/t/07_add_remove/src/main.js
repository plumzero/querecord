import { createApp } from 'vue'

import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import { createRouter, createWebHashHistory } from 'vue-router'

import App from './App.vue'

import DemoOne from './components/DemoOne.vue'

const app = createApp(App)

const routes = [
    { 
        path: '/demo1', component: DemoOne
    }
]

const router = createRouter({
    history: createWebHashHistory(),
    routes: routes
})

app.use(ElementPlus)
app.use(router)

app.mount('#app')
