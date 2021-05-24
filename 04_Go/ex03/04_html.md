
[无拓展解析](04/ParseFiles_1th.go)

[示例一模板解析](04/ParseFiles_2th.go)
```html
    <ol>
        {{range $.images}}
        <li><a href="/view?id={{.|urlquery}}">{{.|html}}></a></li>
        {{end}}
    </ol>
```
* 双大括号`{{}}`是区分模板代码和 HTML 的分隔符，括号里边可以是要显示输出的数据，或者控制语句，比如 `if` 判断或者 range 循环体等。
* `range` 语句在模板中是一个循环过程体，紧跟在 range 后面的必须是一个 `array`、`slice` 或者 `map` 类型的变量。
* `.|formatter` 表示对当前这个元素的值以 formatter 方式进行格式化输出，比如 `.|urlquery}` 即表示对当前元素的值进行转换以适合作为 URL 一部分，而 `{{.|html` 表示对当前元素的值进行适合用于 HTML 显示的字符转化，比如 `>` 会被转义成`&gt;`。
* 如果 range 关键字后面紧跟的是 map 这样的多维复合结构，循环体中的当前元素可以用 `.key1.key2.keyN` 这样的形式表示。 
