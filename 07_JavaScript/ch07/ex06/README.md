
### 学习目标

* 利用 DOM 技术去获取和设置 CSS 信息


### 三位一体的网页

我们在浏览器里看到的网页其实是由以下三层信息构成的一个共同体:
* `结构层`: 由 HTML 或 XHTML 之类的标记语言负责创建。通过标签对网页内容的语义含义进行描述。
* `表示层`: 由 CSS 负责完成，CSS 描述页面内容应该如何呈现。
* `行为层`: 负责内容应该如何响应事件这一问题，这部分由 JavaScript 语言和 DOM 主导。

三种技术之间存在着一些潜在的重叠区域，比如用 DOM 可以改变网页的结构、利用 CSS 中 `:hover` 和 `:focus` 之类的伪类允许你根据用户触发事件改变元素的呈现效果、以及这里要说的利用 DOM 样式给元素设定样式。


### 通过 style 属性获取样式

文档的每个元素节点都可以有一个属性 `style`，这个属性包含着元素的样式，查询这个属性将返回一个对象而不是一个简单的字符串。样式都存放在这个 style 对象的属性里:
```js
    element.style.property
```
下面是一个通过 style 属性设置 `<p>` 元素样式例子:
```html
    <p id="example" style="color: grey; font-family: 'Arial', sans-serif;">
    An example of a paragraph
    </p>
```

[示例一](example_1.html)

CSS 中通过连字符 `-` 表示的属性，在 DOM 中要求替换为驼峰命名表示。如 CSS 属性 `font-family` 在 DOM 中是 `fontFamily`:
```js
    element.style.fontFamily
```

如果在设置 CSS `font-size` 属性以 em 为单位，相应的 DOM `fontSize` 属性也将以 em 为单位。

[示例二](example_2.html)

通过 style 属性使用样式不是一种好办法，它把表现信息与结构混杂在一起了。

可以将 CSS 样式存入一个外部文件，并在页面文件中通过如下形式链接使用样式: 
```js
    <link rel="stylesheet" media="screen" href="styles/styles.css" />
```
此时样式虽然声明在外部，但还可以像之前那样作用到 HTML 内容上。不过与使用 style 属性不同，来自外部文件 styles.css 的样式已经不能再用 DOM style 属性像下面这样检索出来了:
```js
    alert("The font size is " + para.style.fontSize);
```

在外部样式表里声明的的样式不会进入 style 对象，在文档的 `<head>` 部分里声明的样式也是如此:
```html
    <style>
        p#example {
            color: grey;
            font: 12px 'Arial', sans-serif;
        }
    </style>
```

### 通过 DOM 设置样式

通过 CSS 声明样式的具体做法主要有三种。

* 第一种是为标签元素统一地声明样式:
  ```css
    p {
        font-size: 1em;
    }
  ```
* 第二种是为有特定 class 属性的所有元素统一声明样式:
  ```css
    .fineprint {
        font-size: 1.2em;
    }
  ```
* 第三种是为有独一无二的 id 属性的元素单独声明样式:
  ```css
    #intro {
        font-size: 1.2em;
    }
  ```

虽然可以方便地使用 DOM 设置样式，但不建议那样做。

[通过DOM设置样式的示例](example_3.html)

何时该用 DOM 脚本设置样式呢？这里说明了三种适合通过 DOM 对文档样式进行设置的场景。

1. 根据元素在节点树里的位置来设置样式

CSS 还无法根据元素之间的相对位置关系找出某个特定的元素。比如，如果想要为每个 h1 元素后面的那个元素设置样式，单纯地使用 CSS 就无法做到，这个时候就可以结合 DOM 。

[根据位置设置样式示例](story.html)

2. 根据某种条件反复设置某种样式

[交替改变表格中行的背景色示例](itinerary.html)

3. 响应事件

何时应该使用 CSS 来设置样式，何时应该使用 DOM 来设置样式并不总是那么容易决定。比如 CSS 提供的 `:hover` 等伪 class 属性允许我们根据 HTML 元素的状态来改变样式。DOM 也可以通过 `onmouseover` 等事件对 HTML 元素的状态变化做出响应。

最简单的答案是选择最容易实现的方法。比如说，如果想让链接在鼠标指针悬停在其上时改变颜色、或者想让某行在鼠标指针悬停其上时其文本变为粗体，就应该选用 CSS:
```css
    a:hover {
        color: #c60;
    }
    tr:hover {
        font-wight: bold;
    }
```

但所有的浏览器并不一定对 CSS 伪类都能提供完整的支持，但对 DOM 却都有着良好的支持。所以在浏览器们对 CSS 的支持进一步完善之前，在事件发生时用 DOM 改变 HTML 元素的样式更切合实际。

[鼠标指针悬停在某个表格行上方式把该行文本加黑加粗示例](itineraryHover.html)


### 通过 class 属性设置样式

如上所述，我们可以通过 DOM 属性在某些场景下设置内容样式。但这样的话就不得不埋头于 JavaScript 函数中去寻找和修改与设置样式有关的语句，这不是一种理想的做法。

有一种简明的解决方案: 通过 JavaScript 代码去更新这个元素的 class 属性，让浏览器根据这个属性更新 CSS 样式。

[根据位置设置样式示例版二](storySetByClass.html)

[交替改变表格中行的背景色示例版二](itinerarySetByClass.html)