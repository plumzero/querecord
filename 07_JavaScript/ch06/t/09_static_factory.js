
class Person {
    constructor(age) {
        this.age_ = age;
    }
    sayAge() {
        console.log(this.age_);
    }
    static create() {
        return new Person(Math.floor(Math.random() * 100));
    }
}

console.log(Person.create());
console.log(Person.create());
