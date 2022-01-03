
在 JavaScript 中，函数也是对象，而函数名就是指向函数的指针。

函数通常以函数声明的方式定义:
```js
    function sum(num1, num2) {
        return num1 + num2;
    }
```

另一种定义函数的语法是函数表达式:
```js
    let sum = function(num1, num2) {
        return num1 + num2;
    };
```

还有一种定义函数的方式，叫作"箭头函数":
```js
    let sum = (num1, num2) => {
        return num1 + num2;
    };
```


ES6 的所有函数对象都会暴露一个只读的 `name` 属性，其中包含关于函数的信息。多数情况下，这个属性中保存的就是一个函数标识符，或者说是一个字符串化的变量名。即使函数没有名称，也会如实显示成空字符串。
```js
    function foo() {}
    let bar = function() {};
    let baz = () => {};

    console.log(foo.name);
    console.log(bar.name);
    console.log(baz.name);
    console.log((() => {}).name);
```

[函数名示例](t/00_function.js)
