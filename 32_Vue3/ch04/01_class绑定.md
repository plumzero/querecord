
### 对象语法

通过为 `v-bind:class` 传入不同的对象值，可以动态切换 class:
```html
    <div v-bind:class="{ active: isActive }"></div>
```

`v-bind:class` 指令也可以与普通的 class attribute 共存。当有如下模板:
```html
    <div
        class="static"
        v-bind:calss="{ active: isActive, 'text-danger':hasError }"
    ></div>
```
对于如下 data:
```js
    data: {
        isActive: true,
        hasError: false
    }
```
结果渲染为:
```html
    <div class="static active"></div>
```
当 isActive 或者 hasError 变化时，class 列表将相应地更新。例如，如果 hasError 的值为 true，class 列表将变为  `static active text-danger`。

绑定的数据对象不必内联定义在模板里:
```js
    data: {
        classObject: {
            active: true,
            'text-danger':false
        }
    }
```
渲染的结果和上面一样。

也可以在这里绑定一个返回对象的计算属性:
```html
    <div v-bind:class="classObject"></div>
```

```js
    data: {
        isActive: true,
        error: null
    },
    computed: {
        classObject: function() {
            return {
                active: this.isActive && ! this.error,
                'text-danger': this.error && this.error.type === 'fatal'
            }
        }
    }
```

### 数组语法

可以把一个数组传给 `v-bind:class`，以达到应用一个 class 列表的效果:
```html
    <div v-bind:class="[activeClass, errorClass]"></div>
```

```js
    data: {
        activeClass: 'active',
        errorClass: 'text-danger'
    }
```
渲染为:
```html
    <div class="active text-danger"></div>
```

也可以应用三元表达式达到根据条件切换 class:
```html
    <div v-bind:class="[ isActive ? activeClass : '', errorClass ]"></div>
```
这样写将始终添加 errorClass，但只有在 isActive 为 true 时才添加 activeClass 。

不过，当有多个条件 class 时这样写有些繁琐。所以在数组语法中也可以使用对象语法:
```html
    <div v-bind:class="[ { active: isActive }, errorClass ]"></div>
```

### 用于组件中

当在一个自定义组件上使用 class property 时，这些 class 将被添加到该组件的根元素上面。而该根元素上已经存在的 class 不会被覆盖。

例如，对于下面的组件:
```js
    Vue.component('my-component', {
        template: '<p class="foo bar">Hi</p>'
    })
```
之后为上面的组件添加一些 class:
```html
    <my-component class="bar boo"></my-component>
```

HTML 将被渲染为:
```html
    <p class="foo bar baz boo">Hi</p>
```

组件中也可以进行数组绑定:
```html
    <my-component v-bind:class="{ active: isActive }"></my-component>
```
当 isActive 为真时，HTML 将被渲染成为:
```html
    <p class="foo bar active">Hi</p>
```
