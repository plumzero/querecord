
import { createStore } from 'vuex'

const Store = createStore({
    state() {
        return {
            userName: '',
            userPassword: '',
        }
    },
    getters: {
        isLogin: (state) => {
            return state.userName.length > 0
        }
    },
    mutations: {
        // 注销
        clearUserInfo(state) {
            state.userName = '';
            state.userPassword = '';
        },
        // 登录
        registUserInfo(state, {name, password}) {
            state.userName = name;
            state.password = password;
        }
    }
})

export default Store
