
function Person() {}

Person.prototype.name = 'Nicholas';
Person.prototype.age = 29;
Person.prototype.job = 'Software Engineer';
Person.prototype.sayName = function() {
    console.log(this.name);
};

function hasPrototypeProperty(object, name) {
    return ! object.hasOwnProperty(name) && (name in object);
}

let person1 = new Person();
let person2 = new Person();
console.log('name' in person1);
console.log(hasPrototypeProperty(person1, 'name'));

person1.name = 'Greg';
console.log('name' in person1);
console.log(hasPrototypeProperty(person1, 'name'));

delete person1.name;
console.log('name' in person1);
