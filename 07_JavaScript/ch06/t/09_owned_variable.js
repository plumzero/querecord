
class Person {
    constructor() {
        this.name = '';
    }

    type = 'Default';
}

let p1 = new Person();
let p2 = new Person();

p1.name = 'Jim';
p2.name = 'Lily';

console.log(p1.name);
console.log(p2.name);

p2.type = 'ABC';

console.log(p1.type);
console.log(p2.type);
