function * generatorFn() {
    console.log('come here');
    yield 'foo';
    yield 'bar';
    return 'baz';
}

let g = generatorFn();

console.log('would call next first:');
console.log(g.next());              // 遇到 yield 时，会退出生成器对象，同时将 yield 关键字后的值赋值给 value 返回
console.log('would call next second:');
console.log(g.next());
console.log('would call next third:');
console.log(g.next());

// 打印如下
/**
    would call next first:
    come here
    { value: 'foo', done: false }
    would call next second:
    { value: 'bar', done: false }
    would call next third:
    { value: 'baz', done: true }
 */
