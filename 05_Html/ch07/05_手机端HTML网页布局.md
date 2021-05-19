
### 制作手机端的HTML网页

```html
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="maxinum-scale=1.0, mininum-scale=1.0, user-scalable=0, width=device-width, initial-scale=1.0">
        <title>手机端的HTML网页</title>
        <style type="text/css">
            header{width:100%; height:50px; background:rgb(200,150,0);}
            aside{width:20%; height:500px; background:rgb(100,150,200); float:left;}
            section{width:80%; height:500px; background:rgb(100,200,150); float:left;}
            footer{width:100%; height:50px; background:rgb(200,200,200); float:left;}
        </style>
    </head>
    <body>
        <header></header>
        <aside></aside>
        <section></section>
        <footer></footer>
    </body>
    </html>
```
在制作手机端的 HTML 页面时，要在 head 元素中添加相应子元素 `meta`，具体代码如下:
```html
    <meta name="viewport" content="maxinum-scale=1.0, mininum-scale=1.0, user-scalable=0, width=device-width, initial-scale=1.0">
```
上述代码是用于手机屏幕缩放设置:
* `maxinum-scale=1.0, mininum-scale=1.0` 表示最大最小缩放比例都为1，即不允许单击缩放。
* `user-scalable=0` 表示用户不可以手动缩放。
* `width=device-width` 表示显示窗口宽度是客户端的屏幕宽度。
* `initial-scale=1.0` 表示显示的文字和图形的初始比例是 1.0 。

### 测试手机端的HTML网页

以 firefox 浏览器为例，点击菜单工具栏右上角的`打开应用程序菜单`，在弹出的下拉菜单中找到`Web开发者`选项，点击进入"Web开发者"小页面。点击`响应式设计模式`，即可看到手机下的页面，如下:

![手机HTML页面](phone_htmp.jpg)

### 制作 section 元素内容

```html
    <figure>
        <figcaption>我喜欢的图像</figcaption>
        <img src="like1.jpg" width="80%" height="100"><br><br>
        <img src="like2.jpg" width="80%" height="100">
    </figure>
    <figure>
        <figcaption>我喜欢的动画</figcaption>
        <img src="1.gif" width="80%" height="100"><br><br>
        <img src="2.jpg" width="80%" height="100">
    </figure>
    <figure>
        <figcaption>我喜欢的MP3音乐</figcaption>
        花海飞歌: <audio src="花海飞歌.mp3" controls></audio><br><br>
        时间都去哪儿了: <audio src="时间都去哪儿了.mp3" controls></audio>
    </figure>
```

为了防止新添加的内容处在 footer 元素下面，需要修改 section 元素的 CSS 样式:
```css
    section{width:80%; height:500px; background:rgb(100,200,150); float:left; overflow:auto;}
```
增加的 `overflow:auto` 表示当内容超出元素容器时会自动添加滚动条。

为 body 元素添加 CSS 样式，删除网页的四周空白区域:
```css
    body{margin:0px;}
```

### 制作 header 元素内容

在 header 元素标签中添加代码:
```html
    <img src="aa.png" width="60px" height="40px">
    <h3>我的收藏</h3>
```

为上面的 h3 添加 CSS 样式:
```css
    h3{display:inline; padding:6px; color:blue;}
```

### 制作 aside 元素内容

在 aside 元素中添加代码:
```html
    <p align="center">
        <a href="#my1">图像</a><br>
        <a href="#my2">动画</a><br>
        <a href="#my3">音乐</a><br>
    </p>
```
这里实现了三个锚链接，所以要为之前的三个 figure 元素分别添加 id 属性。

### 制作 footer 元素内容

在 footer 元素中添加代码:
```html
    
```