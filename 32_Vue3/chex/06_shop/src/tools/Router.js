
import { createRouter, createWebHashHistory } from 'vue-router'
import Login from '../components/login/Login.vue'
import Home from '../components/home/Home.vue'
import Order from '../components/order/Order.vue'
import Store from '../tools/Storage.js'

const Router = createRouter({
    history: createWebHashHistory(),
    routes: [
        {
            path: '/login',
            component: Login,
            name: 'login'
        },
        {
            path: '/home',
            component: Home,
            name: 'home',
            children: [
                {
                    path: 'order/:type',        // 0 普通订单, 1 秒杀订单
                    component: Order,
                    name: 'Order'
                }
            ],
            redirect: '/home/order/0'   // 用户登录完成后，访问系统主页时，默认重定向到(普通)订单模块
        }
    ]
})

Router.beforeEach((from) => {
    let isLogin = Store.getters.isLogin;
    if (isLogin || from.name == 'login') {
        return true
    } else {
        return { name: 'login' }        // 路由跳转到登录页面
    }
})

export default Router
