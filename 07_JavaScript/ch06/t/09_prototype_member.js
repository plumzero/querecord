
class Person {
    constructor() {}

    // 在类块中定义的所有内容都会定义在类的原型上
    locate() {
        console.log('prototype');
    }
}

let p = new Person();

p.locate();                     // prototype


let p2 = new Person();

console.log(p.locate === p2.locate);    // true
