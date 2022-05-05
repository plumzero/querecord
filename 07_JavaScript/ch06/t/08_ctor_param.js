
class Person {
    constructor(name) {
        console.log(arguments.length);
        this.name = name || null;
    }
}

let p1 = new Person;
console.log(p1.name);   // null

let p2 = new Person();
console.log(p2.name);

let p3 = new Person('Jake');
console.log(p3.name);
