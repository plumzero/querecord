
在基于 MVC 模型的 Web 架构中，将不变的部分提出成为模板，而可变部分由后端程序提供数据，借助模板引擎渲染来生成动态网页。

模板的诞生是为了将显示与数据分离(前后端分离)。

Go 语言提供了 html/template 包，用于生成可对抗代码注入的安全 HTML 文档。它的使用方法简单归纳如下:
- 模板文件的后缀名通常是 .tmpl 和 .tpl(也可以使用其他的后缀)，必须使用 UTF-8 编码。
- 模板文件中使用 `{{` 和 `}}` 来包裹和标识需要传入的数据，它也称为 `Action`。
- 传给模板的数据可以通过 `.` 来访问。如果是复合类型的数据，则可以通过 `{{.FieldName}}` 来访问它的字段。
- 除了 `{{` 和 `}}` 包裹的内容外，其他内容均不做修改原样输出。

Go 语言模板引擎的使用分为: 定义模板文件、解析模板文件和渲染模板文件。

1. 定义模板文件: 按照相应的语法规则去定义模板文件。

2. 解析模板文件: html/template 包提供了以下方法来解析模板文件，获得模板对象。

| 方法或函数名 | 说明 |
|:------------|:-----|
| `func New(name string) *Template` | 创建一个模板对象，并为其添加一个模板名称 |
| `func (t *Template) Parse(src string) (*Template, error)` | 创建模板对象，并完成解析模板内容 |
| `func ParseFiles(filenames ...string) (*Template, error)` | 解析模板文件，并返回对应的模板对象 |
| `func ParseGlob(pattern string) (*Template, error)` | 批量解析文件，pattern 支持正则匹配 |

3. 渲染模板文件: html/template 包提供了 `Execute()` 和 `ExecuteTemplate()` 方法来渲染模板，这两个方法的定义如下:
```go
    func (t *Template) Execute(wr io.Writer, date interface{}) error {}
    func (t *Template) ExecuteTemplate(wr io.Writer, name string, data interface{}) error {}
```
- 在创建 New() 函数时就为模板对象添加了一个模板名称，执行 Execute() 方法后会默认去寻找该名称进行数据融合。
- 使用 ParseFiles() 函数可以一次加载多个模板，此时不可以使用 Execute() 来执行数据融合，可以通过 ExecuteTemplate() 方法指定模板名称来执行数据融合。


### 模板的简单使用

模板语法都包含在 "{{" 和 "}}" 中间，其中 "{{.}}" 中的点表示当前对象。

[对象融合示例程序](t/11_tmpl_object.go)      [对象融合示例模板](t/11_tmpl_object.tmpl)

可以通过将模板应用于一个数据结构来执行并输出 HTML 文档。模板在执行时会遍历数据结构，根据 "." 来访问结构体的对应字段并替换。

[结构体融合示例程序](t/11_tmpl_struct.go)     [结构体融合示例模板](t/11_tmpl_struct.tmpl)


### 嵌入模板

`ParseFiles()` 函数支持加载多个模板文件，模板对象的名字则是第一个模板文件的文件名。

如果需要把数据传递到指定模板执行渲染，可以使用 `ExecuteTemplate()`，这个方法可用于执行指定名字的模板，因为在多个模板文件加载情况下，需要指定特定的模板渲染执行。

比如这里有一个名为 `Layout.html.tmpl` 的模板:
```tmpl
    {{define "layout"}}

    <!doctype html>
    <head>
        <meta charset="UTF-8">
        <meta name="Author" content="">
        <meta name="Keywords" content="">
        <meta name="Description" content="">
        <title>Go</title>
    </head>
    <body>
        {{.}}

        {{template "index"}}
    </body>

    {{end}}
```
如上，模板文件开头定义了模板名字 `{{define "layout"}}`。同时在模板 layout 中，通过 `{{template "index"}}` 嵌入了模板 `index`，也就是第二个模板文件 `index.html.tmpl`，其内容如下:
```tmpl
    {{define "index"}}

    <div>
    <b>Go Usage!</b>
    </div>
    {{end}}
```
下面的代码，通过 `ExecuteTemplate(w, "layout", "Hello World!")` 为名字为 layout 的模板传入字符串:
```go
    t, err := template.ParseFiles("layout.html.tmpl", "index.html.tmpl")
    t.ExecuteTemplate(w, "layout", "Hello World!")
```

* [嵌套模板使用示例](t/11_tmpl_embed.go)
* [嵌套模板使用示例二](t/11_tmpl_multi.go)


### 模板语法

管道是指产生数据的操作，按这个定义 "{{.}}"、"{{.Name}}" 都可以称为管道。可以在 Action 中初始化一个变量来捕获管道的执行结果，其初始化语法为: `$variable := pipeline`。声明变量的 Action 不会产生任何输出。变量可以通过 "{{$variable}}" 方式引用。

Go 模板语法中的条件判断有以下几种:
```template
    {{if pipeline}} T1 {{end}}
    {{if pipeline}} T1 {{else}} T0 {{end}}
    {{if pipeline}} T1 {{else if pipeline}} T0 {{end}}
```

在 Go 的模板语法中，可以使用 `range` 关键字遍历管道，此时 pipeline 必须是数据、切片、字典或者通道。其语法以 `{{range pipeline}}` 开头，以 `{{end}}` 结尾，形式如下:
```template
    {{range pipeline}} T1 {{end}}
```

[range使用示例](t/11_tmpl_range.go)

如果 pipeline 的值其长度为 0，则不会有任何输出。中间也可以有 `{{else}}`，例如:
```template
    {{range pipeline}} T1 {{else}} T0 {{end}}
```
如果 pipeline 的值其长度为 0，则会执行 T0 。

[pipe使用示例](t/11_tmpl_pipeline.go)

在 Go 的模板语法中，`with` 关键字和 if 关键字有点类似，"{{with}}" 操作仅在传递的管道不为空时有条件地执行其主体。形式如下:
```template
    {{with pipeline}} T1 {{end}}
```
如果 pipeline 为空，则不产生输出。中间也可以加入 "{{else}}"，示例如:
```template
    {{with pipeline}} T1 {{else}} T0 {{end}}
```
如果 pipeline 为空，则不改变 "." 并执行 T0，否则将 "." 设为 pipeline 的值并执行 T1 。

----
Go 语言模板支持自定义函数，它通过调用 Funcs() 方法实现，其定义如下:
```go
    func (t *Template) Funcs(funcMap FuncMap) *Template
```
`Funcs()` 方法向模板对象的函数字典里加入参数 funcMap 内的键值对。如果 funcMap 的某个键值对的值不是函数类型，或者返回值不符合要求，则会报 panic 错误，但可以对模板对象的函数列表的成员进行重写。Funcs() 方法返回模板对象以便进行链式调用。FuncMap 类型的定义如下:
```go
    type FuncMap map[string]interface{}
```
`FuncMap()` 类型定义了函数名字符串到函数的映射，每个函数都必须有 1 个或 2 个返回值。如果有 2 个返回值，则后一个必须是 error 接口类型；如果有 2 个返回值的方法返回 error 非 nil，则模板执行会中断并返回该错误给调用者。

[自定义函数使用示例](t/11_tmpl_funcs.go)


[更多语法规则](11_syntax.md)