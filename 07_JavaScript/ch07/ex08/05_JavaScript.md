
### 页面突出显示

每当我们基于模板页面创建一个新页面时，都要向 `<article>` 元素中插入标记。对要设计的站点而言，这一部分正是每个页面之间不同的地方。

理想情况下，还应该更新每个页面 `<nav>` 元素中的链接。比如，如果当前页面是 index.html，那么导航里面就没有必要添加指向当前 index.html 页面的链接了。

但在实际的网站开发中，不太可能一页一页地编辑导航链接。更常见的做法是通过服务器端包含技术，把包含导航标记的片段插入到每个页面中。这里我们就假设服务器端会包含下列代码块：
```html
    <header>
        <img src="images/logo.gif" alt="Jay Skript and the Domsters">
        <nav>
            <ul>
                <li><a href="index.html" class="here">Home</a></li>
                <li><a href="about.html">About</a></li>
                <li><a href="photos.html">Photos</a></li>
                <li><a href="live.html">Live</a></li>
                <li><a href="contact.html">Contact</a></li>
            </ul>
        </nav>
    </header>
```
服务器端包含的优点是可以把重用标记块集中保存。这样，等到以后要更新页面头部或者导航链接时，只要修改一个文件就可以了。但集中保存的缺点，就是不能在每个页面中自定义这个块。

通过 JavaScript 在导航处添加一个 "here" 的 class 属性可以达到这个目的。

通过给每个页面的 body 元素添加 id 属性，可以为每个页面应用不同的样式。


### JavaScript 幻灯片

大多数访客都要先访问主页，在其中添加一些炫酷功能是非常有必要的。

制作一个幻灯片吧，将它放在文档中的 "intro" 段落后面。
