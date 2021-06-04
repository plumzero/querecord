
## 说明
- 一个导演可以拍摄多种题材的电影，如恐怖片或幽默片。每种题材的电影其剧本结构大致是一
  样的(都包括人物，时间，地点，事件等)。可以将每种剧本看作是一个建造者，这样导演就可
  以根据不同的建造者拍摄出不同题材的电影。
- 建造者模式比较容易理解，不作详述。

## 具体实现
- 见 realize.cpp

## 相关的设计模式
- Template Method 模式
    + 在 Builder 模式中，Director 角色控制 Builder 角色。
    + 在 Template 模式中，父类控制子类。
- Composite 模式
    + 有些情况下， Builder 模式生成的实例构造了 Composite 模式。
- Abstract Factory 模式
    + Builder 模式和 Abstract Factory 模式都用于生成复杂的实例。
- Facade 模式
    + 在 Builder 模式中，Director 角色通过组合 Builder 角色中的复杂方法向外部提供可以
      简单生成实例的接口(API)(相当于示例程序中的 construct 方法)。
    + Facade 模式中的 Facade 角色则是通过组合内部模块向外部提供可以简单调用的接口(API)。