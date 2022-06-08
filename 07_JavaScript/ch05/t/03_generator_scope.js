
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
