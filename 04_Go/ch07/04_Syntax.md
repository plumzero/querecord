
### 模板标签

`{{ }}` 模板标签用 "{{" 和 "}}" 括起来。

### 注释

`{{/* a comment */}}` 使用 "{{*" 和 "*}}" 来包含注释内容。

### 变量

`{{.}}` 此标签输出当前对象的值。

`{{.Admpub}}` 表示输出对象中字段或方法名称为 Admpub 的值。

当 Admpub 是匿名字段时，可以访问其内部字段或方法，如"Com": `{{.Admpub.Com}}`。如果 Com 是一个方法并返回一个结构体对象，同样也可以访问其字段或方法: `{{.Admpub.Com.Field1}}`。

`{{.Method1 "参数值1""参数值2"}}` 调用方法 Method1，将后面的参数值依次传递给此方法，并输出其返回值。

`{{$admpub}}` 此标签用于输出在模板中定义的名称为 "admpub" 的变量。当 $admpub 本身是一个结构体对象时，可访问其字段 `{{$admpub.Field1}}`。

在模板中定义变量，变量名称用字母和数字组成，并加上 `$` 前缀，采用简式赋值。例如 `{{$x := "OK"}}` 或 `{{$x := pipeline}}`。

### 通道函数

`{{FuncName1}}` 此标签将调用名称为 "FuncName1" 的模板函数(等同于执行 "FuncName1()"，不传递任何参数)并输出其返回值。

`{{FuncName1 "参数值1""参数值2"}}` 此标签将调用 FuncName1("参数值1", "参数值2")，并输出其返回值。

`{{.Admpub|FuncName1}}` 此标签将调用名称为 "FuncName1" 的模板函数(等同于执行 "FuncName1(this.Admpub)"，将竖线 "|" 左边的 ".Admpub" 变量值作为函数参数传送)并输出其返回值。

### 条件判断

`{{if pipeline}} T1 {{end}}` 标签结构为 {{if...}} ... {{end}}。

`{{if pipeline}} T1 {{else}} T0 {{end}}` 标签结构为 {{if...}} ... {{else}} ... {{end}}。

`{{if pipeline}} T1 {{else if pipeline}} T0 {{end}}` 标签结构为 {{if...}} ... {{else if...}} ... {{end}}。

其中 if 后面可以是一个条件表达式(包括通道函数表达式)，也可以是一个字符串变量或布尔值变量。当为字符串变量时，如为空字符串则判断为 false，否则判断为 true 。

### 循环遍历

`{{range $k,$v := .Var}} {{$k}}=>{{$v}} {{end}}` range...end 结构内部如要使用外部的变量，如 .Var2，需要写为: $.Var2(即在外部变量名称前加字符 $)。

`{{range .Var}} {{.}} {{end}}` 将遍历值直接显式出来。

`{{range pipeline}} T1 {{else}} T0 {{end}}` 当没有可遍历的值时，将执行 else 部分。

### 嵌入子模板

`{{template "name"}}` 嵌入名称为 "name" 的子模板。使用前请确保已经用 `{{define "name"}} 子模板内容 {{end}}` 定义好了子模板内容。

`{{template "name" pipeline}}` 将通道的值赋给子模板中的 "."，即"{{.}}"。

示例:
```tmpl
    {{define "T1"}} ONE {{end}}
    {{define "T2"}} TWO {{end}}
    {{define "T3"}} {{template "T1"}} {{template "T2"}} {{end}}
    {{template "T3"}}
```
输出如下:
```
    ONE TWO
```

### 定义局部变量

`{{with pipeline}} T1 {{end}}` 通道的值将赋给该标签内部的 "."。"内部"是指被 {{with pipeline}} ... {{end}} 包围起来的部分，即 T1 所在位置。

`{{with pipeline}} T1 {{else}} T0 {{end}}` 如果通道的值为空，"." 不受影响并且执行 T0。否则，将通道的值赋给 "." 并且执行 T1 。

> {{end}} 标签是 if, with, range 的结束标签。

### 输出字符串

`{{"\"output\""}}` 输出一个字符串常量。

'{{`"output"`}}' 输出一个原始字符串常量。

`{{printf "%q""output"}}` 函数调用，相当于 printf("%q", "output")。

`{{"output"|printf "%q"}}` 竖线左边的结果作为函数最后一个参数，相当于 printf("%q", "output")。

### 预定义的模板全局函数

`{{and x y}}` 模板全局函数 and，如果 x 为值，返回 y，否则返回 x 。相当于 Go 中的 x && y 。

`{{call .X.Y 1 2}}` 模板全局函数 call，后面的第一个参数的结果必须是一个函数(即这是一个函数类型的值)，其余参数作为该函数的参数。
该函数必须返回 一个或两个结果值，其中第二个结果值是 error 类型。如果传递的参数与函数定义的不匹配或返回的 error 值不为 nil，则停止执行。

### 布尔函数

`{{eq arg1 arg2}}` 返回表达式 "arg1 == arg2" 的布尔值。

`{{ne arg1 arg2}}` 返回表达式 "arg1 != arg2" 的布尔值。

`{{lt arg1 arg2}}` 返回表达式 "arg1 < arg2" 的布尔值。

`{{le arg1 arg2}}` 返回表达式 "arg1 <= arg2" 的布尔值。

`{{gt arg1 arg2}}` 返回表达式 "arg1 > arg2" 的布尔值。

`{{ge arg1 arg2}}` 返回表达式 "arg1 >= arg2" 的布尔值。

布尔函数对任何零值返回 false，非零值返回 true。

对于简单的多路相等测试，eq 只接受两个参数进行比较，后面其他的参数将依次与第一个参数进行比较。例如:
```tmpl
    {{eq arg1 arg2 arg3 arg4}}
```
就相当于
```sh
    arg1==arg2 || arg1==arg3 || arg1==arg4
```
