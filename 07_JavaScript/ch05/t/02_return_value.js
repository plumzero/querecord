
function * generatorFn() { return 'foo'; }

let g = generatorFn();

console.log(g);
console.log(g.next());