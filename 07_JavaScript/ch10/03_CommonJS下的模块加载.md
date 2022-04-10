
CommonJS 规范概述了同步声明依赖的模块定义。这个规范主要用于在`服务器端`实现模块化代码组织，但也可用于定义在浏览器中使用的模块依赖。CommonJS 模块语法不能在浏览器中直接运行。

### require 和 exports

CommonJS 依赖几个全局属性如 require 和 module.exports 。使用 `require()` 指定依赖，而使用 `exports` 对象定义自己的公共 API。 示例:
```js
    var moduleB = require('./moduleB');

    module.exports = {
        stuff: moduleB.doStuff
    };
```
moduleA 通过使用模块定义的相对路径来指定自己对 moduleB 的依赖。

请求模块会加载相应模块，而把模块赋值给变量也非常常见，但赋值给变量不是必需的。调用 require() 意味着模块会原封不动地加载进来:
```js
    console.log('moduleA');
    require('./moduleA');
```
无论一个模块在 require() 中被引用多少次，`模块永远是单例`。模块第一次加载后会被缓存，后续加载会取得缓存的模块:
```js
    console.log('moduleA');
    var a1 = require('./moduleA');
    var a2 = require('./moduleA');

    console.log(a1 === a2);     // true
```
[测试代码](t/03_singeton.js)

在 CommonJS 中，模块加载是模块系统执行的同步操作。因此 require() 可以像下面这样以编程方式嵌入在模块中:
```js
    console.log('moduleA');
    if (loadCondition) {
        require('./moduleA');
    }
```
如果 moduleA 已经在前面某个地方加载过了，这个条件 require() 就意味着只暴露 moduleA 这个命名空间而已。

### 使用模块内容

Node.js 中可以使用绝对或相对路径，也可以使用安装在 node_modules 目录中依赖的模块标识符，去解析模块引用。

指向模块定义的路径可能引用一个目录，也可能是一个 JavaScript 文件，无论是什么，这与本地模块实现无关，而 moduleB 被加载到本地变量中。moduleA 在 module.exports 对象上定义自己的公共接口，即 foo 属性。

如果有模块想使用这个接口，可以像下面这样导入它:
```js
    var moduleA = require('./moduleA');

    moduleA.stuff();    
```
注意，`此模块不导出任何内容`(在定义模块时也必须保证这个)。即使它没有公共接口，如果应用程序请求了这个模块，那也会在加载时执行这个模块体。

### 再说 exports

如果只想导出一个实体，可以直接给 module.exports 赋值:
```js
    module.exports = 'foo';
```
这样，整个模块就导出一个字符串，可以像下面这样使用:
```js
    var moduleA = require('./moduleB');

    console.log(moduleB);   // 'foo'
```

导出多个值也很常见，可以使用对象字面量赋值或每个属性赋一次值来实现:
```js
    module.exports = {
        a: 'A',
        b: 'B'
    };

    // 等价操作
    module.exports.a = 'A';
    module.exports.b = 'B';
```

模块的一个主要用途是托管类定义:
```js
    // moduleA.js
    class A {}

    module.exports = A;

    // test.js
    var A = require('./moduleA');

    var a = new A();
```
也可以将类实例作为导出值:
```js
    class A {}

    module.exports = new A();
```
此外，CommonJS 也支持动态依赖:
```js
    if (condition) {
        var A = require('./moduleA');
    }
```
