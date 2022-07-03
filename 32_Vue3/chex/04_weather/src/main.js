import { createApp } from 'vue'
import VueAxios from 'vue-axios'
import axios from 'axios'
import ElementPlus from 'element-plus'
import App from './App.vue'

const app = createApp(App)
app.use(VueAxios, axios)
app.use(ElementPlus)
app.mount('#app')
