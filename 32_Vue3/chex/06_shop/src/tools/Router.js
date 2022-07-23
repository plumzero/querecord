
import { createRouter, createWebHashHistory } from 'vue-router'
import Login from '../components/login/Login.vue'
import Home from '../components/home/Home.vue'
import Order from '../components/order/Order.vue'
import Goods from '../components/goods/Goods.vue'
import AddGood from '../components/goods/AddGood.vue'
import ManagerList from '../components/manager/ManagerList.vue'
import ManagerReqList from '../components/manager/ManagerReqList.vue'
import ManagerOrder from '../components/manager/ManagerOrder.vue'
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
                },
                {
                    path: 'goods/:type',        // 0 普通商品 1 秒杀商品 2 今日推荐
                    component: Goods,
                    name: 'Goods'
                },
                {
                    path: 'addGood/:type',      // 0 普通商品 1 秒杀商品 2 今日推荐
                    component: AddGood,
                    name: 'AddGood'
                }
            ],
            redirect: '/home/order/0'   // 用户登录完成后，访问系统主页时，默认重定向到(普通)订单模块
        },
        {
            path: 'ownerList',
            component: ManagerList,
            name: 'ManagerList'
        },
        {
            path: 'ownerreq',
            component: ManagerReqList,
            name: 'ManagerReqList'
        },
        {
            path: 'ownerorder',
            component: ManagerOrder,
            name: 'ManagerOrder'
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
