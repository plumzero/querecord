import { createApp } from 'vue'
import App from './App.vue'

import { createStore } from 'vuex'

// 创建模块
const module1 = {
    namespaced: true,       // 开启模块的命名空间，模块内部的 Getter、Action、Mutation 都会根据模块的嵌套路径进行命名，实现模块间的完全隔离
    state() {
        return {
            count1: 7
        }
    },
    mutations: {
        increment1(state, payload) {
            state.count1 += payload.count
        }
    }
}

const module2 = {
    namespaced: true,
    state() {
        return {
            count2: 0
        }
    },
    mutations: {
        increment2(state, payload) {
            state.count2 += payload.count
        }
    }
}

const store = createStore({
    modules: {
        HelloWorld1: module1,
        HelloWorld2: module2
    }
})

const app = createApp(App)

app.use(store)

app.mount('#app')
