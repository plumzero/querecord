
### 依赖

npm install vue-router@4 --save

npm install vuex@next --save

npm install element-plus --save

npm install mockjs --save

npm install wangeditor --save

npm install echarts --save


### 文件说明

- src
    - mock
        
    - tools
        - Storage.js: 全局状态配置
        - Router.js: 路由配置
    - components
        - home
            - Home.vue: 用来渲染管理系统的主页
        - login
            - Login.vue: 用来渲染用户登录页面
        - order
            - Order.vue: 订单页面
        - goods
            - Goods.vue: 商品页面
            - AddGood.vue: 


### 说明

- 使用路由进行全局的页面管理，在每次页面跳转前都检查当前的用户登录状态。如果未登录，则将页面重定向到登录页面。
- 通过嵌套路由的方式来管理主页中的管理模块，包括商品管理、订单管理、店铺管理等。
- 主页中包含一个侧边栏菜单和一个主体功能模块。侧边栏用来进行主体功能模块的切换。
