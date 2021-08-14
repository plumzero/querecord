
### 位置

网页元素在浏览器窗口里的位置是一种表示性的信息，这种位置信息通常由 CSS 负责设置。
```css
    element {
        position: absolute;
        top: 50px;
        left: 100px;
    }
```
这将把 element 元素摆放到距离浏览器窗口的左边界 100 像素，距离浏览器窗口的上边界 50 像素的位置上。

通过 DOM 将文档里的某个元素摆放到特定位置是很容易，改变这个元素的位置也很容易。将元素的显示位置随着时间不断地发生变化，就实现了简单的动画效果。

### 时间

JavaScript 函数 `setTimeout` 能够让某个函数在经过一段预定的时间之后才开始执行。
```js
    setTimeout("function", interval)
```
参数分别表示要执行的函数 function 以及经过多长时间(毫秒)后执行。

根据 setTimeout 调用赋值的返回变量，可以通过 `clearTimeout` 函数取消这个函数的执行:
```js
    variable = setTimeout("function", interval);
    clearTimeout(variable);
```

### 时间递增量

从开始位置到目标位置应该是一个渐变的过程。逻辑应该是这样的:

1. 获得元素的的当前位置。
2. 如果元素已经到达它的目的地，则退出这个函数。
3. 如果元素尚未到达它的目的地，则把它向目的地移近一点儿。
4. 经过一段时间间隔之后从步骤 1 开始重复上述步骤。

[简单动画示例](message.html)

[鼠标放上去时触发动画效果](list.html)
