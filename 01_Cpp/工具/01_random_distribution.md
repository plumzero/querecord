
### 均匀分布

> 离散均匀分布

uniform_int_distribution 类模板定义了分布对象，它返回的是均匀分布在闭合范围`[a,b]`内的随机整数。

模板参数的类型是生成的整数的类型，默认类型是 int 。

一个构造函数有两个用来定义范围的上边界和下边界；下边界的默认值为 0, 上边界的默认值是这种类型所生成的最大值。

[离散均匀分布示例](01_random/04_uniform_int_distribution.cpp)


> 连续均匀分布

uniform_real_distribution 类模板定义了一个默认返回 double 型浮点值的连续分布。