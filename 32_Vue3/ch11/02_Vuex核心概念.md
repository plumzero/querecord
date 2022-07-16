
这里介绍 Vuex 中的 5 个核心概念: state, Getter, mutation, action, module 。

### state

状态实际上就是应用中组件需要共享的数据。在 Vuex 中采用单一状态树来存储状态数据，也就是说数据源是唯一的。在任何组件中，都可以使用如下方式来获取任何一个状态树中的数据:
```js
    this.$route.state
```

当组件中所使用的状态数据非常多时，可以使用 Vuex 中提供的 `mapState` 方法来将其直接映射成组件的计算属性进行使用。由于状态数据本身具有响应性，因此将其映射为计算属性后也具有响应性，使用计算属性和直接使用状态数据并无不同。示例代码如下:
```html
<template>
    <h1>计数器1: {{count}}</h1>
    <button @click="increment">增加</button>
</template>
<script>
import { mapState } from 'vuex'
export default {
    methods: {
        increment() {
            this.$store.commit('increment')
        }
    },
    computed: mapState(['count'])
}
</script>
```
如果组件使用的计算属性的名字与 store 中定义的状态名字不一致，也可以在 mapState 中传入对象来进行配置:
```html
<template>
    <h1>计数器: {{countData2}}</h1>
    <button @click="increment">增加</button>
</template>
<script>
import { mapState } from 'vuex'
export default {
    methods: {
        increment() {
            this.$store.commit('increment')
        }
    },
    computed: mapState({
        // 通过字符串映射
        countData: 'count',
        // 通过函数映射
        countData2(state) {
            return state.count
        }
    })
}
</script>
```

### Getter

在 Vue 中，计算属性实际上就是 Getter 方法。

当需要将数据处理过再进行使用时，就可以使用计算属性。对于 Vuex 来说，借助 mapState 方法，可以将状态映射为计算属性，从而增加一些所需的业务逻辑。但是如果有些计算属性是通用的，或者这些计算属性也是多组件共享的，此时在这些组件中都实现一遍这些计算方法就显得非常多余。

Vuex 提供了具有响应性的 Getter 方法，当其内部使用的状态发生改变时，其也会触发所绑定组件的更新。
```js
const store = createStore({
    state() {
        return {
            count: 0
        }
    },
    // 定义修改状态的方法
    mutations: {
        increment(state) {
            state.count++
        }
    },
    getters: {
        countText(state) {
            return state.count + '次'
        }
    }
})
```
在组件中使用 store 的 Getter 数据方法如下:
```html
<template>
    <h1>计数器1: {{this.$store.getters.countText}}</h1>
    <button @click="increment">增加</button>
</template>
```

Getter 方法也支持参数的传递:
```js
getters: {
    countText(state) {
        return (s) => {
            return state.count + s
        }
    }
}
```
使用方式如下:
```js
this.$store.getters.countText('次')
```

对于 Getter 方法，Vuex 也提供了一个方法将其映射到组件内部的计算属性中:
```html
<template>
    <h1>计数器: {{countText('次')}}</h1>
    <button @click="increment">增加</button>
</template>
<script>
import { mapGetters } from 'vuex'
export default {
    methods: {
        increment() {
            this.$store.commit('increment')
        }
    },
    computed: mapGetters([
        'countText'
    ])
}
</script>
```

### Mutation

在 Vuex 中，修改 store 中的某个状态数据的唯一方法是提交 Mutation ，将数据变动的行为封装为函数并定义在 mutations 选项中即可，示例如下:
```js
mutations: {
    increment(state) {
        state.count++
    }
}
```
通过调用 store 实例的 commit 方法进行提交来触发 Mutation:
```js
this.$store.commit('increment')
```

在调用 commit 方法提交修改的时候，也支持传递参数:
```js
mutations: {
    increment(state, n) {
        state.count += n;
    }
}
```
调用示例如下:
```js
this.$store.commit('increment', 2)
```

也可以传递一个对象:
```js
mutations: {
    increment(state, payload) {
        state.count += payload.count
    }
}
```
提交示例如下:
```js
this.$store.commit({
    type: 'increment',
    count: 2
})
```
其中，type 表示要调用的修改状态的方法名，其他的属性即要传递的参数。

### Action

Mutation 只能同步地对数据进行修改，Vuex 提供了 Action 来异步修改数据，比如网络请求数据后刷新页面。

Action 可以认为是对 Mutation 进行包装，之后通过提交 Mutation 来实现状态的改变。这样在 Action 定义的方法中允许开发者包含任意的一步操作。
```js
const store = createStore({
    state() {
        return {
            count: 0
        }
    },
    mutations: {
        increment(state, payload) {
            state.count += payload.count
        }
    },
    actions: {
        asyncIncrement(context, payload) {
            setTimeout(() => {
                context.commit('increment', payload)
            }, 3000)
        }
    }
})
```
上面的代码模拟了异步操作。另外 Action 本身是可以接收参数的，第一个参数是与 store 实例有着相同方法和属性的上下文对象，第二个参数是自定义对象。

在组件中使用 Action 时，需要通过 store 实例对象的 `dispath` 方法来触发:
```js
this.$store.dispatch('asyncIncrement', { count: 2 })
```

### Module

Module 是 Vuex 进行模块化编程的一种方式。

Vuex 允许将 store 分割成模块，每个模块拥有自己的 state、mutations、actions、getters，甚至可以嵌套拥有自己的子模块。

[工程示例](t/02_module)

Vuex 中的 Module 支持动态注册，可以根据实际需要决定是否新增一个 Vuex 的 store 模块。模块的动态注册通过 `registerModule` 实现:
```js
const module2 = {
    namespaced: true,
    state() {
        return {
            count2: 0
        }
    },
    mutations: {
        increment2(state, payload, root) {
            state.count2 += payload.count
            root.state.HelloWorld2.count += payload.count
        }
    }
}

const store = createStore({})

store.registerModule('HelloWorld2', module2)
```
