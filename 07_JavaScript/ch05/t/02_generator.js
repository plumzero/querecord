
"use strict";

console.log("--- 生成器也实现了 Iterator 接口 ---");
{
    function* generatorFn() {}
    
    const g = generatorFn();

    console.log(g);
    console.log(g.next);
}

console.log("--- 生成器返回值 ---");
{
    function* generatorFn() {
        return 'foo';
    }

    let generatorObject = generatorFn();

    console.log(generatorObject);
    console.log(generatorObject.next());
}

console.log("--- 生成器函数只会在初次调用 next() 方法后开始执行 ---");
{
    function* generatorFn() {
        console.log('foobar');
    }

    // 因为生成器的懒加载机制，初次调用生成器函数并不会打印日志
    let generatorObject = generatorFn();
    console.log('xx');

    generatorObject.next(); // 打印: foobar
}

console.log("--- 生成器对象作为可迭代对象会更方便 ---");
{
    function* generatorFn() {
        yield 1;
        yield 2;
        yield 3;
    }

    for (const x of generatorFn()) {
        console.log(x);
    }
}

console.log("--- 使用生成器定义可迭代对象 ---");
{
    function* nTimes(n) {
        while (n--) {
            console.log('yield');
            yield;
        }
    }

    for (let _ of nTimes(3)) {
        console.log('foo');
    }
}

console.log("--- 生成一个索引生成器 ---");
{
    function* nTimes(n) {
        for (let i = 0; i < n; i++) {
            yield i;
        }
    }

    for (let x of nTimes(3)) {
        console.log(x);
    }

    // while 实现
    function* nTimes2(n) {
        let i = 0;
        while(n--) {
            yield i++;
        }
    }

    for (let x of nTimes2(3)) {
        console.log(x);
    }
}

console.log("--- 实现范围和填充数组 ---");
{
    function* range(start, end) {
        while (end > start) {
            yield start++;
        }
    }

    for (const x of range(4, 7)) {
        console.log(x);
    }

    function* zeros(n) {
        while (n--) {
            yield 0;
        }
    }

    console.log(Array.from(zeros(8)));
}

console.log("--- 使用 yield* 迭代一个可迭代对象 ---");
{
    function* generatorFn() {
        yield* [1, 2, 3];
    }
    // 和下面的代码等价
    // function* generatorFn() {
    //     for (const x of [1, 2, 3]) {
    //         yield x;
    //     }
    // }
    let generatorObject = generatorFn();

    for (const x of generatorFn()) {
        console.log(x);
    }
}

console.log("--- 使用 yield* 实现递归 ---");
{
    function* nTimes(n) {
        if (n > 0) {
            yield* nTimes(n - 1);
            yield n - 1;
        }
    }

    for (const x of nTimes(3)) {
        console.log(x);
    }
}

console.log("--- 生成一个随机的双向图 ---");
{
    class Node {
        constructor(id) {
            this.id = id;
            this.neighbors = new Set();
        }

        connect(node) {
            if (node !== this) {
                this.neighbors.add(node);
                node.neighbors.add(this);
            }
        }
    }

    class RandomGraph {
        constructor(size) {
            this.nodes = new Set();

            for (let i = 0; i < size; i++) {
                this.nodes.add(new Node(i));
            }

            const threshold = 1 / size;
            for (const x of this.nodes) {
                for (const y of this.nodes) {
                    if (Math.random() < threshold) {
                        x.connect(y);
                    }
                }
            }
        }

        print() {
            for (const node of this.nodes) {
                const ids = [...node.neighbors]
                                .map((n) => n.id)
                                .join(',');
                console.log(`${node.id}: ${ids}`);
            }
        }
        // 图是否连通
        isConnected() {
            const visitedNodes = new Set();

            function* traverse(nodes) {
                for (const node of nodes) {
                    if (!visitedNodes.has(node)) {
                        yield node;
                        yield* traverse(node.neighbors);
                    }
                }
            }
            // 取得集合中的第一个节点
            const firstNode = this.nodes[Symbol.iterator]().next().value;

            // 使用递归生成器迭代每个节点
            for (const node of traverse([firstNode])) {
                visitedNodes.add(node);
            }

            return visitedNodes.size === this.nodes.size;
        }
    }

    const g = new RandomGraph(6);

    g.print();

    console.log(g.isConnected());
}

console.log("--- 生成器作为默认迭代器 ---");
{
    class Foo {
        constructor() {
            this.values = [1, 2, 3];
        }
        * [Symbol.iterator]() {
            yield* this.values;
        }
    }

    const f = new Foo();
    for (const x of f) {
        console.log(x);
    }
}

console.log("--- 生成器的三种方法 next/return/throw ---");
{
    function* generatorFn() {}
    
    const g = generatorFn();

    console.log(g);
    console.log(g.next);
    console.log(g.return);
    console.log(g.throw);
}

console.log("--- 使用 return 终止生成器 ---");
{
    function* generatorFn() {
        for (const x of [1, 2, 3]) {
            yield x;
        }
    }

    const g = generatorFn();

    console.log(g);
    console.log(g.return(4));
    console.log(g);
}

console.log("--- for-of 循环等内置语言结构会忽略状态为 done: true 的 IteratorObject 内部返回的值 ---");
{
    function* generatorFn() {
        for (const x of [1, 2, 3]) {
            yield x;
        }
    }

    const g = generatorFn();

    for (const x of g) {
        if (x > 1) {
            g.return(4);
        }
        console.log(x);
    }
}