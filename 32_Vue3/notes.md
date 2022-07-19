
### 快速查找

- [mockjs示例](http://mockjs.com/examples.html#)
- [关于Blob](https://developer.mozilla.org/zh-CN/docs/Web/API/Blob/Blob)


### 触发路由的两种方式

- router-link
- this.$router


### 定位问题的思路

遇到的主要问题有三个方面:
- 一种是书写不符合语法规则产生的错误。这种一般程序会抛出异常，可以根据异常的描述去查看问题。
- 一种是变量是否存在，比如错把 items 写成 item 等。表现在渲染的页面与预期不一致，简单的办法是打印变量。
- 最后一种是类型改变，比如 1 ,由原来的 number 改变为 string 类型。


### 可忽略的警告

类似下面的代码:
```html
    <el-menu-item
        v-for="item in items"
        :index="item.index"
        :key="item.index"
    >
        <div id="text">{{item.title}}</div>
    </el-menu-item>
```
可能会报如下警告:
```sh
[Vue warn]: Invalid prop: type check failed for prop "index". Expected String | Null, got Number with value 0.
```
可以将 `:index="item.index"` 改为 `:index="item.index+''"` 来去除，不过也可以忽略这个警告。

### 关于 package-lock.json

这个文件建议在 '.gitignore' 中忽略掉。
