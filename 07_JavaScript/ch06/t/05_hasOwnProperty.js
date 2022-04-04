
function Person() {}

Person.prototype.name = 'Nicholas';
Person.prototype.age = 29;
Person.prototype.job = 'Software Engineer';
Person.prototype.sayName = function() {
    console.log(this.name);
};

let person1 = new Person();
let person2 = new Person();
console.log(person1.hasOwnProperty('name'));

person1.name = 'Greg';
console.log(person1.hasOwnProperty('name'));

delete person1.name;
console.log(person1.hasOwnProperty('name'));
