

从一个简单的 meson 工程开始说起。
```
    project('simple', 'c')
    executable('myexe', 'source.c')
```
`project` 用于指定工程的名称 *simple* 及编程语言 *c*，使用单引号括起来。

`executable` 用于指定创建目录名称 *myexe* 以及源文件 *source.c* 。


当然，源文件也可以通过变量进行引用:
```
    project('simple', 'c')
    src = 'source.c'
    executable('myexe', src)
```

如果源文件比较多，可以放在数组里进行引用:
```
    project('simple', 'c')
    src = ['source1.c', 'source2.c', 'source3.c']
    executable('myexe', src)
```