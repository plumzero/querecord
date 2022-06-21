
### mixin 技术

将某些共同的部分抽离出来，作为独立的功能模块，而其他组件则可以混入此功能模块对象。这就是组件的 mixin 技术。

[mixin示例](t/03_mixin.html)

当混入对象与组件中定义了相同的选项时，Vue 可以对这些选项进行合并。不冲突的配置将完整合并，冲突的配置会以组件中自己的配置为准。

[mixin选项的合并示例](t/03_mixin_merge.html)

生命周期函数的这些配置项的混入与属性类的配置项的混入略有不同，不重名的生命周期函数会被完整混入组件，重名的生命周期函数被混入组件时，在函数触发时，会先触发 mixin 对象中的实现，再触发组件内部的实现。

[mixin与生命周期函数示例](t/03_mixin_life.html)

Vue 也支持对应用进行全局 mixin 混入。直接对应用实例进行 mixin 设置即可:
```js
    const App = Vue.createApp({})
    App.mixin({
        mounted() {
            console.log('Mixin 对象 mounted')
        }
    })
```
虽然全局 Mixin 使用起来很方便，但是其会使之后所有注册的组件都默认被混入这些选项。

### teleport 功能

利用此功能，开发者可以将相关行为的逻辑和 UI 封装到同一个组件中，以提高代码的聚合性。

[利用teleport将全局弹窗挂载在body元素下示例](t/03_teleport.html)
