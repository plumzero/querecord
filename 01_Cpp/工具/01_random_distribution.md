
### 均匀分布

> 离散均匀分布

uniform_int_distribution 类模板定义了分布对象，它返回的是均匀分布在闭合范围`[a,b]`内的随机整数。

模板参数的类型是生成的整数的类型，默认类型是 int 。

一个构造函数有两个用来定义范围的上边界和下边界；下边界的默认值为 0, 上边界的默认值是这种类型所生成的最大值。

[离散均匀分布示例](01_random/04_uniform_int_distribution.cpp)

[离散均匀应用示例](01_random/06_cards_distribution.cpp)

> 连续均匀分布

uniform_real_distribution 类模板定义了一个默认返回 double 型浮点值的连续分布。

[连续均匀分布示例](01_random/05_uniform_real_distribution.cpp)

> 标准均匀分布

标准均匀分布是一个在范围 `[0,1)` 内的连续分布。

generate_canonical() 的函数模板会提供一个浮点值范围在 `[0,1)` 内，且有给定的随机比特数的标准均匀分布。

generate_canonical() 有 3 个模板参数: 浮点类型，尾数的随机比特个数，以及使用的随机数生成器的类型。

generate_canonical() 的参数是一个随机数生成器，因此最后一个模板参数可以推导出来。

[标准均匀分布示例](01_random/07_standard_uniform_distribution.cpp)


### 正态分布

正态分布是由两个参数完全定义的: 期望和标准差。

normal_distribution 模板定义了可以产生随机浮点值的分布对象类型，默认是 double 类型。

默认构造函数创建的是标准正态分布，即期望是 0，方差是 1.0 。

[正态分布示例](01_random/08_normal_distribution.cpp)

[正态分布直方图示例](01_random/09_normal_distribution_histogram.cpp)


### 对数分布

对数分布和表示随机变量的正态分布有关，这些值的对数分布是一个正态分布。

对数分布是由期望和标准差定义的，但这些参数和变量无关，它们和变量的对数相关。

对于大自然中的很多随机变量来说，对数分布比正态分布更接近概率的表示。病人的感染率就是一个对数分布模式。

lognormal_distribution 模板的一个实例定义了一个默认返回浮点类型值的对数分布对象。

[对数分布示例](01_random/10_lognormal_distribution.cpp)

[对数分布直方图示例](01_random/11_lognormal_distribution_histogram.cpp)


### 抽样分布

> 离散分布

discrete_distribution 模板定义了返回随机整数的范围在 `[0,n)` 内的分布，基于每个从 0 到 n-1 的可能值的概率权重。

[离散分布示例](01_random/12_discrete_distribution.cpp)

> 分段常数分布

piecewise_constant_distribution 模板定义了一个在一组分段子区间生成浮点值的分布。给定子区间内的值是均匀分布的，每个子区间都有自己的权重。

[分段常数分布示例](01_random/13_piecewise_constant_distribution.cpp)

> 分段线性分布

piecewise_linear_distribution 模板定义了浮点值的连续分布，它的概率密度函数是从一系列的样本值所定义的点得到的。每个样本值的权重都决定了它的概率密度值。

[分段线性分布示例](01_random/14_piecewise_linear_distribution.cpp)


### 泊松分布

poisson_distribution 模板定义了可以生成随机非负数的函数对象类型，随机非负数模式是 int 类型。

[泊松分布示例](01_random/15_poisson_distribution.cpp)


### 几何分布

几何分布是一个离散分布，它被用来模拟取得某种有两个可能结果的事件所需要的实验次数。

geometric_distribution 模板定义了返回非负整数值的离散分布类型，返回的非负整数值默认是 int 类型。

[几何分布示例](01_random/16_geometric_distribution.cpp)


### 指数分布

指数分布可以模拟事件发生之间的时间。可以把它想象成一个连续等值的几何分布。

exponential_distribution 模板定义了返回浮点值的分布类型，浮点值默认是 double 类型。

[指数分布示例](01_random/17_exponential_distribution.cpp)

