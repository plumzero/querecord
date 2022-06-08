function * generatorFn() {}

console.log(generatorFn);
console.log(generatorFn()[Symbol.iterator]);

console.log(generatorFn());
console.log(generatorFn()[Symbol.iterator]());

// 迭代器自引用
let g = generatorFn();
console.log(g === g[Symbol.iterator]());