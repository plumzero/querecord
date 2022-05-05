
class Person {
    sayName() {
        console.log(`${Person.greeting} ${this.name}`);
    }
}

// 在类上定义数据成员
Person.greeting = 'My name is';
// 在原型上定义数据成员
Person.prototype.name = 'Jake';

let p = new Person();
p.sayName();    // My name is Jake

let p2 = new Person();

console.log(p.name === p2.name);            // true
console.log(p.greeting === p2.greeting);    // true
console.log(Person.prototype);
console.log(Person);

Person.prototype.name = 'Jack';
p.sayName();

Person.greeting = 'Your name is';
p2.sayName();

// 无论是在类上定义数据成员，还是在原型上定义数据成员，其对所有实例都是共享的。

