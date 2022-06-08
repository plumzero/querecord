
function * generatorFn() {}

let g = generatorFn();      // 产生一个 生成器对象

console.log(g);             // 一开始处于挂起状态
console.log(g.next());      // 开始或恢复执行
