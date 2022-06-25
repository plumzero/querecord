
Vue 组件在页面中被插入、移除或者更新的时候都可以附带转场效果，即可以展示过渡动画。

### 定义过渡动画

Vue 过渡动画的核心原理是采用 CSS 类来实现的，只是 Vue 会在组件的不同生命周期自动切换不同的 CSS 类。

Vue 默认提供了一个名为 `transition` 的内置组件，可以用其来包装要展示过渡动画的组件。`transition` 组件的 `name` 属性用来设置要执行的动画名称，Vue 中约定了一系列 CSS 类名规则来定义各个过渡过程中的组件状态。
```css
    .ani-enter-from {
        width: 0px;
        height: 0px;
        background-color: red;
    }
    .ani-enter-active {
        transition: width 2s, height 2s, background-color 2s;
    }
    .ani-enter-to {
        width: 100px;
        height: 100px;
        background-color: blue;
    }
    .ani-leave-from {
        width: 100px;
        height: 100px;
        background-color: blue;
    }
    .ani-leave-active {
        transition: width 2s, height 2s, background-color 3s;
    }
    .ani-leave-to {
        width: 0px;
        height: 0px;
        background-color: red;
    }
```
上面的代码中定义了 6 个特殊的 CSS 类，其用法如下:
```js
    <transition name="ani">
        <div v-if="show">
        </div>
    </transition>
```
在上述代码中，并没有显式地对上面的 6 个类进行使用。为 transition 组件的 name 属性设置动画名称 "ani" 后，当组件被插入、页面被移除时，其会自动寻找此动画名称开头的 CSS 类，这些类的格式及意义如下:
- `x-enter-from`: 在组件即将被插入页面时被添加到组件上，可以理解为组件的初始状态，元素在被插入页面后此类会马上被移除。
- `x-enter-active`: 在组件的整个插入过渡动画中都会被添加，直到组件的过渡动画结束后才会被移除。可以在这个类中定义组件过渡动画的时长、方式、延迟等。 
- `x-enter-to`: 在组件被插入页面后立即被添加，此时 x-enter-from 类会被移除，可以理解为组件过渡的最终状态。
- `x-leave-from`: 在组件即将被移除时此类会添加。用来定义移除组件时过渡动画的起始状态。
- `x-leave-active`: 在组件的整个移除过渡动画中都会被添加，直到组件的过渡动画结束后才会被移除。可以在这个类中定义组件过渡动画的时长、方式、延迟等。
- `x-leave-to`: 对应地用来移除组件动画的终止状态。

其中，x 表示定义的过渡动画名称。

[Vue过渡动画示例](t/03_vue_animation.html)

上面 6 种特殊的 CSS 类虽然被添加的时机不同，但是最终都会被移除，因此当动画执行完成后，组件的样式并不会保留。更常见的做法是在组件本身绑定一个最终状态的样式类:
```html
    <transition name="ani">
        <div v-if="show" class="demo">
        </div>
    </transition>
```
CSS 代码如下:
```css
    .demo {
        width: 100px;
        height: 100px;
        background-color: blue;
    }
```

### 设置动画过程中的监听回调

对于组件的加载或卸载过程，有一系列的生命周期函数会被调用。对于 Vue 中的转场动画来说，也可以注册一系列的函数来对其过程进行监听。

[示例](t/03_transition_listen.html)

### 多个组件的过渡动画

Vue 中的 transition 组件支持同时包装多个互斥的子组件元素，从而实现多组件的过渡效果。在实际开发中，有很多这类常见的场景，例如元素 A 消失的同时元素 B 展示。

[示例](t/03_transition_components.html)

默认情况下，两个元素的插入和移除会同步进行，如果想要在移除动画执行完成后，再执行插入动画，只需要将 transition 组件的 `mode` 属性设置为 `out-in` 即可。而 `in-out` 属性值则会先执行插入动画，再执行移除动画。
```html
    <transition name="ani" mode="in-out"></transition>
```

### 列表过渡动画

在 Vue 中，通常使用 v-for 指令来动态构建列表视图。在动态构建列表视图的过程中，其中的元素经常会有增删、重排等操作。在 Vue 中使用 `transition-group` 组件可以方便地实现列表元素变动的动画效果。

[示例](t/03_list_animation.html)

如果要使用列表动画，列表中的每一个元素都需要有一个唯一的 key 值。

[优化用户列表页面示例](t/03_userlist_animation.html)
