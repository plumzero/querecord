
### header 布局元素

`header`元素用来设置 HTML 网页的头部，即一个网页的标题部分，通常包括标题、Logo标识、导航栏等内容。

header 元素的标签为 `<header></header>`。示例代码如下:
```html
    <header>我是网页头部</header>
```

需要注意的是，header 元素是 body 元素的子元素，即 header 元素需要定义在 body 元素之中。

header 元素定义好之后，需要通过 CSS 样式进行格式定义。示例代码如下:
```css
    <style type="text/css">
        body{height: 600px}
        header{width:100%; height:10%; background:rgb(200,0,0);}
    </style>
```
上面的代码指定了 body 的具体格式，而 header 元素的宽度和高度百分比是相对 body 元素来说的。rgb() 函数定义了 header 元素的背景色。


### footer 布局元素

`footer`元素用来设置 HTML 网页的底部，通常包括友情链接、版权声明、联系方式等内容。

footer 元素的标签是 `<footer></footer>`。示例代码如下:
```html
    <footer>我是网页底部</footer>
```

同样，footer 元素也是 body 元素的子元素，也要放在 body 元素之中。

footer 元素定义好之后，需要通过 CSS 样式进行格式定义。示例代码如下:
```css
    footer{width:100%; height:8%; background:rgb(0,100,0)}
```

[示例](t/01_header_footer.html)
