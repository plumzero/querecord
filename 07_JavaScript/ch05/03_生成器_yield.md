
### 生成器对象执行的中断和恢复

`yield` 关键字可以让生成器停止和开始执行。

生成器函数在遇到 yield 关键字之前会正常执行，遇到这个关键字后，执行会停止，函数作用域的状态会被保留。停止执行的生成器函数只能通过在生成器对象上调用 `next()` 方法来恢复执行。
```js
    function * generatorFn() {
        yield;
    }

    let g = generatorFn();

    console.log(g.next());  // { value: undefined, done: false }
    console.log(g.next());  // { value: undefined, done: true }
    console.log(g.next());  // { value: undefined, done: true }
```
[示例程序](t/03_yield_exp.js)

通过 yield 关键字退出的生成器函数会处在 'done: false' 状态，通过 return 关键字(可省略)退出的生成器函数会处于 'done: true' 状态:
```js
    function * generatorFn() {
        yield 'foo';
        yield 'bar';
        return 'baz';
    }

    let g = generatorFn();

    console.log(g.next());
    console.log(g.next());
    console.log(g.next());
```
[示例程序](t/03_yield_value.js)

对于生成器对象的执行记住三条:
- 通过 next() 方法会开始或恢复生成器对象的执行
- 执行中遇到 yield 会退出生成器对象，同时将 yield 后的值(若有)赋值给 value, 将 done 置为 false
- 执行结束(或遇 return 返回)后也会退出生成器对象，同时将返回值(若有)赋值给 value, 将 done 置为 true

### 作用域隔离

生成器函数内部的执行流程会针对每个生成器对象区分作用域。简单来说，就是一个生成器对象上调用 next() 不会影响其他生成器。
```js
    function * generatorFn() {
        yield 'foo';
        yield 'bar';
        return 'baz';
    }

    let g1 = generatorFn();
    let g2 = generatorFn();

    console.log(g1.next());
    console.log(g2.next());
    console.log(g2.next());
    console.log(g1.next()); 
```
[示例程序](t/03_generator_scope.js)


### 生成器对象作为可迭代对象

之前说过，生成器对象实现了 Iterable 接口，且它们默认的迭代器是自引用的。所以生成器对象可以作为可迭代对象:
```js
    function * generatorFn() {
        yield 1;
        yield 2;
        yield 3;
    }

    for (let x of generatorFn()) {
        console.log(x);
    }
```

利用这个特性，实现一个计数器:
```js
    function * nTimes(n) {
        while (n--) {
            yield;
        }
    }

    for (let _ of nTimes(3)) {
        console.log('foo');
    }
```

