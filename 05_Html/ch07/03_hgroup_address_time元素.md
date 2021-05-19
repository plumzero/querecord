
### hgroup 元素

`hgroup` 元素是将标题和它的子标题进行分组的元素。hgroup 元素一般会把 h1~h6 的元素进行分组，比如在一个内容区块的标题和它的子标题算是一组。

通常情况下，文章只有一个主标题时，是不需要 hgroup 元素的。

hgroup 元素的标签是 `<hgroup></hgroup>`，通常放在 header 元素中。


### address 元素

`address` 元素通常是用来定义作者信息的，如作者姓名、电子邮箱、真实地址、电话号码等。

address 元素的标签是 `<address></address>`，通常放在 footer 元素中。

需要注意的是，address 元素中的内容以斜体显示。


### time 元素

`time` 元素可以定义很多格式的时期和时间，示例代码如下:
```html
    <time datetime="2021-05-19" pubdate="pubdate">文章发布于 2021 年 5 月 19 日</time>
```
`pubdate` 是个可选标签，加上它后，浏览器就可以很方便地识别出文章或新闻发布的日期。

[三种元素使用示例](t/03_hgroup_address_time.html)
