
### 显示和隐藏动画效果

在 jQuery 中，可以通过在 `show()` 和 `hide()` 方法中加入相应的参数来实现带有"动画效果"的显示和隐藏，语法格式如下:
```js
    $().hide(speed, callback);
    $().show(speed, callback);
```
参数`speed`为必选参数，表示动画执行的速度，单位是毫秒。可选的`callback`参数是隐藏或显示完成后所执行的函数名称。

在 jQuery 中，也可以使用 `toggle()` 方法来"切换"元素的"显示状态"。其语法格式如下:
```js
    $().toggle(speed, callback);
```
参数意义同上。

[显示、隐藏和切换动画效果](t/03_show_state.html)


### 淡入和淡出动画效果

在 jQuery 中，可以使用 `fadeIn()` 方法来实现元素的淡入效果，使用 `fadeOut()` 方法来实现元素的淡出效果，语法格式如下:
```js
    $().fadeIn(speed, callback);
    $().fadeOut(speed, callback);
```
`speed` 为可选参数，表示动画执行的速度，单位为毫秒。`callback`为可选参数，表示动画执行完成之后的回调函数。

在 jQuery 中，利用 `fadeToggle()` 方法可以在 fadeIn() 和 fadeOut() 方法之间进行切换。语法格式如下:
```js
    $().fadeToggle(speed, callback);
```
参数意义同上。

在 jQuery 中，利用 `fadeTo()` 方法允许渐变为给定的不透明度(值介于 0.0 与 1.0 之间)。语法格式如下:
```js
    $().fadeTo(speed, opacity, callback);
```
`opacity` 为必选参数，表示元素指定的透明度，取值范围为 0.0~1.0。其余参数意义同上。

[淡入和淡出动画效果](t/03_fade.html)


### 滑动动画效果

在 jQuery 中，可以使用 `slideUp()` 实现元素的滑上动车效果，使用 `slideDown()` 方法来实现元素的滑下动车效果，语法格式如下:
```js
    $().slideDown(speed, callback);
    $().slideUp(speed, callback);
```

在 jQuery 中，`slideToggle()` 方法可以在 slideDown() 与 slideUp() 方法之间进行切换。语法格式如下:
```js
    $().slideToggle(speed, callback);
```

[滑动动画效果](t/03_slide.html)


### 自定义动画

在 jQuery 中，使用 `animate()` 方法来实现自定义动画。语法格式如下:
```js
    $().animate({params}, speed, callback);
```
`params`参数是必选参数，用来定义形成动画的 CSS 属性。

[自定义动画示例](t/03_animate.html)
