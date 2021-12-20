
Symbol (符号)的用途是确保对象属性使用唯一标识符，不会发生属性冲突的危险。

### 基本用法

符号需要使用 `Symbol()` 函数初始化。因为符号本身是原始类型，所以 typeof 操作符对符号返回 symbol 。
```js
    let sym = Symbol();
    console.log(typeof sym);
```

调用 Symbol() 函数时，也可以传入一个字符串参数作为对符号的描述(description)，将来可以通过这个字符串调试代码。但是这个字符串参数与符号定义或标识完全无关。

### 使用全局符号注册表

如果运行时的不同部分需要共享和重用符号实例，那么可以用一个字符串作为键，在全局符号注册表中创建并重用符号。此时要用到 `Symbol.for()` 方法。
```js
    let fooGlobalSymbol = Symbol.for('foo');        // 创建新符号
    let otherFooGlobalSymbol = Symbol.for('foo');   // 重用已有符号

    console.log(fooGlobalSymbol == otherFooGlobalSymbol);
```

即便采用相同的符号描述，在全局注册表中定义的符号跟使用 Symbol() 定义的符号也并不等同:
```js
    let localSymbol = Symbol('foo');
    let globalSymbol = Symbol.for('foo');

    console.log(localSymbol == globalSymbol);
```
全局注册表中的符号必须使用字符串键来创建，因此作为参数传给 Symbol.for() 的任何值都会被转换为字符串。

还可以使用 `Symbol.keyFor()` 来查询全局注册表，这个方法接收符号，返回该全局符号对应的字符串键。如果查询的不是全局符号，则返回 undefined 。
```js
    // 创建全局符号
    let s = Symbol.for('foo');
    console.log(Symbol.keyFor(s));

    // 创建普通符号
    let s2 = Symbol('bar');
    console.log(Symbol.keyFor(s2));
```
