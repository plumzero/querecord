
let Person = function(name, age, job) {
    this.name = name;
    this.age = age;
    this.job = job;
    this.sayName = function() {
        console.log(this.name);
    };
}

let person1 = new Person('Nicholas', 29, 'Software Engineer');
let person2 = new Person('Greg', 27, 'Doctor');

person1.sayName();
person2.sayName();

console.log(person1.constructor === Person);
console.log(person2.constructor === Person);

console.log(person1 instanceof Object);
console.log(person1 instanceof Person);
console.log(person2 instanceof Object);
console.log(person2 instanceof Person);

console.log(person1.sayName == person2.sayName);