
function Person() {}

Person.prototype.name = 'Nicholas';
Person.prototype.age = 29;
Person.prototype.job = 'Software Engingeer';
Person.prototype.sayName = function() {
    console.log(this.name);
};

let keys = Object.keys(Person.prototype);
console.log(keys);

let p1 = new Person();
p1.name = 'Rob';
p1.age = 31;
let p1keys = Object.keys(p1);
console.log(p1keys);

let keys2 = Object.getOwnPropertyNames(Person.prototype);
console.log(keys2);
