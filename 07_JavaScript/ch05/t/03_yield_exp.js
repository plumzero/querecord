function * generatorFn() {
    console.log('come here');
    yield;
}

let g = generatorFn();

console.log('would call next first:');
console.log(g.next());
console.log('would call next second:');
console.log(g.next());
console.log('would call next third:');
console.log(g.next());

// 打印如下
/**
    would call next first:
    come here
    { value: undefined, done: false }
    would call next second:
    { value: undefined, done: true }
    would call next third:
    { value: undefined, done: true } 
 */
// 生成器函数对象只会在初次调用 next() 方法后开始执行。
//  生成器对象 g 第一次调用 next() 后，打印 'come here'，之后遇到 yield 关键字，退出生成器函数。
//  因为通过 yield 关键字退出的生成器函数会处在 done: false 状态，所以 g.next() 的调用结果为: { value: undefined, done: false }
// 再次对生成器对象调用 next() 方法会恢复执行。
//  因为通过 return 关键字(上述代码中省略了)退出的生成器函数会处于 done: true 状态，所以 g.next() 的调用结果为: { value: undefined, done: true }
// 以后的调用都会返回上一次的状态。
