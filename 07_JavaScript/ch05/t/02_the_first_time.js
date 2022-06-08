function * generatorFn() { console.log('foobar'); }

let g = generatorFn();

console.log('print this');
g.next();