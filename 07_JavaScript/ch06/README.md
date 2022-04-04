
创建自定义对象的通常方式是创建 Object 的一个新实例，然后再给它添加属性和方法:
```js
    let person = new Object();
    person.name = 'Nicholas';
    person.age = 29;
    person.job = 'Software Engineer';
    person.sayName = function() {
        console.log(this.name);     // this.name 会解析为 person.name
    };
```

使用对象字面量可以这样写:
```js
    let person = {
        name: 'Nicholas',
        age: 29,
        job: 'Software Engineer',
        sayName() {
            console.log(this.name);
        }
    };
```
