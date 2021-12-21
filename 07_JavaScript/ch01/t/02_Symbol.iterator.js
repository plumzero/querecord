
"use strict";

// 目标: 体会懒加载
{
    class Foo {
        *[Symbol.iterator](){ console.log("懒加载测试"); }
    }

    let f = new Foo();

    console.log(f[Symbol.iterator]());

    // 将下面两行解除注释之后，重新执行会打印 '懒加载测试'
    // for (const x of f[Symbol.iterator]()) {
    // }
}

// 目标: 加载数据
console.log("--- 分割线 ---");
{
    class Foo {
        *[Symbol.iterator](){
            yield 1;
            yield 2;
        }
    }

    let f = new Foo();
    
    for (const x of f[Symbol.iterator]()) {
        console.log(x);
    }
}

// 目标: 数据变化了...
console.log("--- 分割线 ---");
{
    var arrVal = [ 1, 2, 3, 4 ];

    class Foo {
        // 因为迭代器是对目标的引用，所以迭代器的结果能够反映数据的变化
        *[Symbol.iterator](){
            for (let i = 0; i < arrVal.length; i++) {
                yield arrVal[i];
            }
        }
    }

    let f = new Foo();
    
    for (const x of f[Symbol.iterator]()) {
        console.log(x);
    }

    arrVal.push(5);
    arrVal.push(6);

    for (const x of f[Symbol.iterator]()) {
        console.log(x);
    }
}

// 目标: 使用别的加载器
console.log("--- 分割线 ---");
{
    function* g1() {
        yield 2;
        yield 3;
        yield 4;
    }

    class Foo {
        *[Symbol.iterator](){
            yield 1;
            yield* g1();
            yield 5;
            yield* Array.from(arguments);   // ... 如果 arguments 换成其他的(比如 args)，就会报错，在 js 中 arguments 也是一个关键字
        }
    }

    let f = new Foo();
    
    for (const x of f[Symbol.iterator](6, 7)) {
        console.log(x);
    }
}

// 书上的例子
// 可以看作是如何为对象实现一个迭代器的示例
console.log("--- 分割线 ---");
{
    class Emitter {
        constructor(max) {
            this.max = max;
            this.idx = 0;
        }

        *[Symbol.iterator]() {
            while (this.idx < this.max) {
                yield this.idx++;
            }
        }
    }

    function count() {
        let emitter = new Emitter(5);
        for (const x of emitter) {
            console.log(x);
        }
    }

    count();
}