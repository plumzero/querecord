
"use strict";

console.log("--- 可迭代对象 ---");
{
    let num = 1;
    let obj = {};

    // 这两种类型没有实现迭代器工厂函数
    console.log(num[Symbol.iterator]);
    console.log(obj[Symbol.iterator]);

    let str = 'abc';
    let arr = ['a', 'b', 'c'];
    let map = new Map().set('a', 1).set('b', 2).set('c', 3);
    let set = new Set().add('a').add('b').add('c');
    
    // 这些类型都实现了迭代器工厂函数
    console.log(str[Symbol.iterator]);
    console.log(arr[Symbol.iterator]);
    console.log(map[Symbol.iterator]);
    console.log(set[Symbol.iterator]);

    // 调用这个工厂函数会生成一个迭代器
    console.log(str[Symbol.iterator]());
    console.log(arr[Symbol.iterator]());
    console.log(map[Symbol.iterator]());
    console.log(set[Symbol.iterator]());
}

console.log("--- 迭代器 ---");
{
    let arr = ['foo', 'bar', 'baz'];

    for (let el of arr) {
        console.log(el);
    }

    // 数组解构
    let [a, b, c] = arr;
    console.log(a, b, c);

    // 扩展操作符
    let arr2 = [...arr];
    console.log(arr2);

    // Array.from()
    let arr3 = Array.from(arr);
    console.log(arr3);

    // Set 构造函数
    let set = new Set(arr);
    console.log(set);

    // Map 构造函数
    let pairs = arr.map((x,i) => [x,i]);
    console.log(pairs);
    let map = new Map(pairs);
    console.log(map);
}

console.log("--- 继承父类的迭代器 ---");
{
    class FooArray extends Array {}
    let fooArr = new FooArray('foo', 'bar', 'baz');

    for (let el of fooArr) {
        console.log(el);
    }
}

console.log("--- next() ---");
{
    let arr = ['foo', 'bar'];
    
    // 获得迭代器
    let iter = arr[Symbol.iterator]();
    console.log(iter);

    // 执行迭代
    console.log(iter.next());
    console.log(iter.next());
    console.log(iter.next());
}

console.log("--- 自定义迭代器 ---");
{
    class Counter {
        constructor(limit) {
            this.limit = limit;
        }

        // 实现 Iterator 接口
        // 每次创建新的迭代器时重置计数， 为此使用闭包实现
        [Symbol.iterator]() {
            let count = 1,
                limit = this.limit;
            return {
                next() {
                    if (count <= limit) {
                        return { done: false, value: count++ };
                    } else {
                        return { done: true, value: undefined };
                    }
                }
            };
        }
    }

    let counter = new Counter(3);
    for (let i of counter) { console.log(i); }

    for (let i of counter) { console.log(i); }
}

console.log("--- 迭代器的 Symbol.iterator 属性对象还是迭代器 ---");
{
    let arr = ['foo', 'bar', 'baz'];
    let iter1 = arr[Symbol.iterator]();

    console.log(iter1[Symbol.iterator]);

    let iter2 = iter1[Symbol.iterator]();

    console.log(iter1 == iter2);
    console.log(iter1 === iter2);
}

console.log("--- 提前终止迭代器 ---");
{
    class Counter {
        constructor(limit) {
            this.limit = limit;
        }

        // 实现 Iterator 接口
        [Symbol.iterator]() {
            let count = 1,
                limit = this.limit;
            return {
                next() {
                    if (count <= limit) {
                        return { done: false, value: count++ };
                    } else {
                        return { done: true, value: undefined };
                    }
                },
                return() {
                    console.log('Exiting early');
                    return { done: true };
                }
            };
        }
    }

    let counter = new Counter(5);
    for (let i of counter) {  
        if (i > 2) {
            break;
        }
        console.log(i);
    }
}

console.log("--- 测试哪种迭代器有 return ---");
{
    let str = 'abc';
    let arr = ['a', 'b', 'c'];
    let map = new Map().set('a', 1).set('b', 2).set('c', 3);
    let set = new Set().add('a').add('b').add('c');
    
    console.log(str[Symbol.iterator]().return);
    console.log(arr[Symbol.iterator]().return);
    console.log(map[Symbol.iterator]().return);
    console.log(set[Symbol.iterator]().return);
}