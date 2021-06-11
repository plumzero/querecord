
### text/template

提供一套数据驱动模板用于产生文本输出。

模板中用来代指数据结构成员(典型的是结构域字段或者映射表键)的注解用于控制执行并将数据展示，模板中被注解的数据又叫`动作(action)`。

输入的模板文件为 UTF-8 编码格式，`动作`通过定界符 `{{` 和 `}}` 注解，其他的文本数据按原样输出。

[模板与数据结构示例](05/ParseStruct.go)


### 动作列表

创建一个名称为 name 的未定义模板:
```go
    func New(name string) *Template
```

```go
    func (t *Template) Parse(text string) (*Template, error)
```