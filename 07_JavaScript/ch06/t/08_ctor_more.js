
class Person {
    // constructor 是静态成员，必须在类块内部定义
    constructor(name) {
        this.say1 = () => {
            console.log('instance member: ', this.name1, this.name2, this.name3);
        }
        this.name1 = name;
    }

    say2 = () => {
        console.log('prototype member: ', this.name1, this.name2, this.name3);
    };    

    static say3 = () => {
        console.log('static member: ', this.name1, this.name2, this.name3);
    }
}

let p1 = new Person('Lily')

Person.prototype.name2 = 'Jake';
Person.name3 = 'Han';

console.log('实例中内容:', p1);                 // { say1: [Function], name1: 'Lily' }  实例中包含了 say1 和 name1，每个实例都有各自的内容，说明实例中的内容是非共享的
console.log('原型中内容:', Person.prototype);   // { say2: [Function], name2: 'Jake' }  原型对象中包含了 say2 和 name2，原型对象中的内容是共享的
console.log('类中内容:', Person);               // [class Person] { say3: [Function: say3], constructor: [Function], name3: 'Han' }

let p2 = new Person('Jack');
p2.age = 18;
console.log('实例中内容:', p2);                 // Person { say1: [Function], name1: 'Jack', age: 18 }
console.log('原型中内容:', Person.prototype);   // { say2: [Function], name2: 'Jake' }
console.log('类中内容:', Person);               // [class Person] { say3: [Function: say3], constructor: [Function], name3: 'Han' }

p1.say1();
p2.say1();
p1.say2();
p2.say2();
Person.say3();

// 从上面的测试中可以看出:
//  ... 慢慢理解吧
