
Vue Router 是 Vue 官方的路由管理器，与 Vue 框架本身深度契合。

Vue Router 支持使用 CDN 的方式引入，也支持使用 NPM 的方式进行安装。

CDN 方式引入:
```sh
    https://unpkg.com/vue-router@4
```

npm 方式引入:
```sh
    npm install vue-router@4 -s
```

Vue Router 导航跳转的全过程。
1. 导航被触发，可以通过 router-link 组件触发，也可以通过 $router.push 或直接改变 URL 触发。
2. 在将要失活的组件中调用 beforeRouteLeave 守卫函数。
3. 调用全局注册的 beforeEach 守卫。
4. 如果当前使用的组件没有变化，调用组件内的 beforeRouteUpdate 守卫。
5. 调用在定义路由时配置的 beforeEnter 守卫函数。
6. 解析异步路由组件。
7. 在被激活的组件中调用 beforeRouteEnter 守卫。
8. 导航被确认。
9. 调用全局注册的 afterEach 守卫。
10. 触发 DOM 更新，页面进行更新。
11. 调用组件的 beforeRouteEnter 函数汇总 next 参数注册的回调函数。
