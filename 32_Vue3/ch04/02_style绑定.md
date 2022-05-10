
### 对象语法

`v-bind:style` 的对象语法是一个 JavaScript 对象，用于定义 CSS 样式。CSS property 名可以用驼峰式(camelCase)或短横线分隔(kebab-case)来命名(驼峰更常用):
```html
    <div v-bind:style="{ color: activeColor, fontSize: fontSize + 'px' }"></div>
```

```js
    data: {
        activeColor: 'red',
        fontSize: 30
    }
```

直接绑定到一个样式对象会让模板更清晰:
```js
    data: {
        styleObject: {
            color: 'red',
            fontSize: '13px'
        }
    }
```
同样，对象语法可以和计算属性结合进行更灵活地使用。

### 数组语法

`v-bind:style` 的数组语法可以将多个样式对象应用到同一个元素上:
```html
    <div v-bind:style="[ baseStyles, overridingStyles ]"></div>
```

### 自动添加前缀

当 `v-bind:style` 使用需要添加浏览器引擎前缀的 CSS property 时，如 `transform`，Vue.js 会自动侦测并添加相应的前缀。

### 多重值

从 2.3.0 起，可以为 style 绑定中的 property 提供一个包含多个值的数组，常用于提供多个带前缀的值。例如:
```html
    <div :style="{ display: ['-webkit-box', '-ms-flexbox', 'flex'] }"></div>
```
这样写只会渲染数组中最后一个被浏览器支持的值。比如，如果浏览器支持不带浏览器前缀的 flexbox, 那么最后会渲染为 `display: flex`。

