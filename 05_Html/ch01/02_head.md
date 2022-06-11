
`<head></head>` 标签用于定义一些特殊的内容，如页面标题、定时刷新、外部文件等。

在 HTML 中，一般来说，只有 6 个标签能放在 head 标签内:
- title
- meta
- link
- style
- script
- base


### title

定义网页的标题。

### meta

一般用于定义页面的特殊信息，例如页面关键字、页面描述等。这些信息不是提供给人看的，而是提供给搜索引擎蜘蛛看的。

在 HTML 中，meta 标签有两个重要的属性: `name` 和 `http-equiv` 。

`name` 属性的取值可以是以下几个:

| 属性值 | 说明 |
|:------|:-----|
| keywords | 网页的关键字，可以是多个 |
| description | 网页的描述 |
| author | 网页的作者 |
| copyright | 版权信息 |

实际开发中，一般只会用到 `keywords` 和 `description` 两个:
```html
    <meta name="keywords" content="关键字信息"/>
    <meta name="description" content="描述性信息"/>
```

meta 的 `http-equiv` 属性只有两个重要作用: 定义网页所使用的编码，以及定义网页自动刷新跳转。

定义网页所使用的编码示例:
```html
    <meta http-equiv="Content-Type" content="text/html"; charset="utf-8"/>
```
这段代码告诉浏览器，该页面所使用的编码是 utf-8 。

定义网页自动刷新跳转:
```html
    <meta http-equiv="refresh" content="6;url=http://www.example.com"/>
```
这段代码表示当前页面 6 秒后会自动跳转到 http://www.example.com 页面。

### style

用于定义元素的 CSS 样式。

### script

用于定义页面的 JavaScript 代码，也可以引入外部 JavaScript 文件。

### link

用于引入外部样式文件。

### base

无太大意义。
