
虽然 Object 的实例没有多少功能，但很适合存储和在应用程序间交换数据。

显式地创建 Object 的实例有两种方式。第一种是使用 new 操作符和 Object 构造函数:
```js
    let person = new Object();
    person.name = "Nicholas";
    person.age = 29;
```
另一种是使用`对象字面量`表示法，这种方法简化了包含大量属性的对象的创建:
```js
    let person = {
        name: "Nicholas",
        age: 29
    };
```
当然也可以用对象字面量表示法来定义一个只有默认属性和方法的对象，只要使用一对大括号:
```js
    let person = {};    // 与 new Object() 相同
    person.name = "Nicholas";
    person.age = 29;
```
在使用对象字面量表示法定义对象时，并不会实际调用 Object 构造函数。

事实上，对象字面量已经成为给函数传递大量可选参数的主要方式，尤其适合传入函数的对象有大量可选参数的情况下。

[对象字面量传入函数](t/01_object_literal.js)

虽然属性一般是通过点语法来存取的，但也可以使用中括号来存取属性。在使用中括号时，要在括号内使用属性名的字符串形式:
```js
    console.log(person["name"]);
    console.log(person.name);
```
从功能上讲，这种方式没有区别。使用中括号的主要优势就是可以通过变量访问属性:
```js
    let propertyName = "name";
    console.log(person["propertyName"]);
```
中括号法也可以用于属性名带空格的字符串或者非字母数字字符的情况。
```js
    person["first name"] = "Nicholas";
    person["1"] = "one";
```
