
### setup 方法

setup 方法是组合式 API 功能的入口方法，如果使用组合式 API 模式进行组件开发，则逻辑代码都要编写在 setup 方法中。

setup 方法会在组件创建之前执行，即对应组件生命周期方法 `beforeCreate` 方法调用之前被执行。因此，在 setup 方法中可以访问组件的传参外部属性 props，但不能使用 this 来引用组件的其他属性。

在 setup 方法的最后，开发者可以将定义的组件所需要的数据、函数等内容暴露给组件的其他选项(比如生命周期函数、业务方法、计算属性等)。

setup 方法可以接收两个参数: `props` 和 `context`。props 是组件使用时设置的外部参数，其是响应式的；context 则是一个 JavaScript 对象，其中可用的属性有 `attrs`、`slots` 和 `emit`。

[setup方法示例](t/03_setup.html)

在 setup 方法的最后可以返回一个 JavaScript 对象，此对象包装的数据可以在组件的其他选项中使用，也可以直接用于 HTML 模板中。
```js
    App.component("com", {
        setup(props, context) {
            let data = 'setup的数据'
            return {
                data
            }
        },
        props: {
            name: String
        },
        template: `<div>{{data}}</div>`
    })
```

[setup方法返回数据示例](t/03_setup_data.html)

如果不在组件中定义 template 模板，也可以直接使用 setup 方法来返回一个渲染模板，当组件将要被展示时，会使用此渲染函数进行渲染。

在 setup 方法中不能使用 this 关键字，setup 方法中的 this 与当前组件实例并不是同一对象。

### 在 setup 方法中定义生命周期行为

setup 方法本身也可以定义组件的生命周期方法，方便将相关的逻辑组合在一起。

setup 方法常用的生命周期定义方法如下:

| 组件原生命周期定义方法 | setup 中的生命周期定义方法 |
|:---------------------|:-------------------------|
| beforeMount | onBeforeMount |
| mounted | onMounted |
| beforeUpdate | onBeforeUpdate |
| updated | onUpdated |
| beforeUnmount | onBeforeUnmount |
| unmounted | onUnmounted |
| errorCaptured | onErrorCaptured |
| renderTracked | onRenderTracked |
| renderTriggered | onRenderTriggered |

setup 方法的执行时机与 beforeCreate 和 created 两个生命周期方法的执行时机基本一致，所以只要在 setup 方法中直接编写代码即可。

[在setup方法中定义生命周期行为示例](t/03_setup_life.html)

如果组件和 setup 方法都定义了同样的生命周期方法，它们之间并不会冲突。在实际调用时，会先调用 setup 方法中定义的，再调用组件内部定义的。

[非组合式API实现用户列表界面示例](t/03_normal.html)

非组合式API实现用户列表时，先在 data 选项中定义属性，之后在 methods 选项中定义功能方法，最后在 watch 选项中监听属性，逻辑点分离，使得代码可读性变差。

将逻辑都梳理在 setup 方法中，相同的逻辑点聚合性更强，便于阅读和扩展。

[组合式API实现用户列表界面示例](t/03_setup_list.html)