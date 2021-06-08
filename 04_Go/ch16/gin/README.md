
<img align="right" width="159px" src="color.png">


### GET 和 POST 方法

[ping pong](01_pingpong.go)

[GET/POST方法](01_get_post.go)


### 路由参数(Parameters in path)

路由参数: 指的是在路由路径中定义的参数，例如请求 URI 为 `/user/42` 时 42 就是路由参数。注意路由参数不是查询字符串，例如`/user?ID=42` 中的 ID=42 才是查询字符串。

使用路由参数的好处是将动态 URL 变为静态 URL，因为请求客户端会认为路由参数不是变化的数据，因此被视为静态 URL 。

若需要定义带有路由参数的路径，需要使用`:param`或`*param`的语法在路径中。二者意义如下:
* `:param`: 完成必选参数的定义。例如 `/user/:ID` 可以匹配 "/user/42"，但不能匹配 "/user" 或 "/user/"。
* `*param`: 完成可选参数的定义。例如 `/user/*ID` 可以匹配 "/user/42"、"/user"、"/user" 。

可以使用 gin.Context 对象的 `c.Param("param")` 来获取路由参数，如果没有匹配到，则返回空字符串。

路由优先级: `精准路由` > `必选路由` > `可选路由`

[路由参数](03_parameters_in_path.go)


### 查询字符串参数(Querystring parameters)

[简单的查询字符串参数](04_querystring_parameters.go)


### 表单上传(Multipart/Urlencoded Form)

[表单上传](05_form_post.go)

[带参数的表单上传&&页面重定向](06_query_and_form_post.go)


### 数据测试



### 认证测试


### 上传文件测试
