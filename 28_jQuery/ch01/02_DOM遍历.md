
### 筛选

假设这里要为所有外部链接添加一个类:
```css
    a.external {
        background: #fff url(images/external.png) no-repeat 100% 2px;
        padding-right: 16px;
    }
```

通过筛选函数，就可以利用 jQuery 的隐式迭代能力，保持代码的简洁:
```js
    $('a').filter(function() {
        return this.hostname && this.hostname != location.hostname;
    }).addClass('external');
```
这里的第二行代码可以筛选出符合下面两个条件的 `<a>` 元素:
* 必须包含一个带有域名(this.hostname)的 href 属性。这个测试可以排除 mailto 及类似链接。
* 链接指向的域名(还是 this.hostname)必须不等于(!=)页面当前所在域的名称(location.hostname)。

更准确地说，`.filter()` 方法会迭代所有匹配的元素，对每个元素都调用传入的函数并测试函数的返回值。如果函数返回 false，则从匹配集合中删除相应元素；如果返回 true，则保留相应元素。

### 为特定单元格添加样式

如果想改为给每个包含 Henry 的单元格的下一个单元格添加样式，可以将已经编写好的选择符作为起点，然后连缀一个 `.next()` 方法即可。
```js
    $(document).ready(function() {
        $('td:contains(Henry)').next().addClass('highlight');
    });
```

要想突出显示 Henry 所在单元格后面的全部单元格，可以使用 `.nextAll()` 方法:
```js
    $(document).ready(
        $('td:contains(Henry)').nextAll().addClass('highlight');
    );
```

类似的还有 `.prev()` 和 `.prevAll()`。`.siblings()` 能够选择处于相同 DOM 层次的所有其他元素，无论这些元素处于当前元素之前还是之后。

要在这些单元格中再包含原来的单元格(即包含 Henry 的那个单元格)，可以添加 `.addBack()` 方法:
```js
    $(document).ready(function() {
        $('td:contains(Henry)').nextAll().addBack().addClass('hightlight');
    });
```

事实上，要选择同一组元素，可以采用的选择符和遍历方法的组合很多。如下是选择包含 Henry 的单元格所在行的另一种方式:
```js
    $(document).ready(function() {
        $('td:contains(Henry)').parent().children().addClass('highlight');
    });
```

### 连缀

在 jQuery 中，可以通过一行代码取得多个元素集合并对这些元素集合执行多次操作，这称为连缀。之所以可以这样做是因为几乎所有jQuery方法都会返回一个 jQuery 对象，因而可连缀调用多个jQuery方法。
```js
    $('td:contains(Henry)').parent().find('td:eq(1)')
        .addClass('highlight').end().find('td:eq(2)')
                               .addClass('highlight');
```
其含义如下:
```js
    $('td:contains(Henry)')     // 取得包含 Henry 的所有单元格
        .parent()               // 取得它的父元素
        .find('td:eq(1)')       // 在父元素中查找第2个单元格
        .addClass('highlight')  // 为该单元格添加 highlight 类
        .end()                  // 恢复到包含 Henry 的单元格的父元素
        .find('td:eq(2)')       // 在父元素中查找第 3 个单元格
        .addClass('highlight'); // 为该单元格添加 highlight 类
```
连缀虽然效率很高，但难于理解。

### 访问  DOM 元素

所有选择符表达式和多数jQuery方法都返回一个 jQuery 对象，通过这个对象可以提供隐式迭代和连缀能力。

jQuery 提供了 `.get()` 方法用于对象的引用。如 .get(0) 表示要访问jQuery对象引用的第一个DOM元素。如果想知道带有 `id="my-element"` 属性的元素的标签名，可以通过如下代码:
```js
    var myTag = $('#my-element').get(0).tagName;
```
也可以简写为:
```js
    var myTag = $('#my-element')[0].tagName;
```
