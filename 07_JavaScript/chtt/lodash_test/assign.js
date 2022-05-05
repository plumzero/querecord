
import _ from 'lodash';

// _.assign(object, [sources])

// 分配来源对象的[可枚举属性]到目标对象上。
// 来源对象的应用规则是从左到右，随后的下一个对象的属性会覆盖上一个对象的属性。

// 注意: 这个方法会改变 object

// 参数:
//  object: 目标对象
//  [sources]: 来源对象
// 返回:
//  返回 object

function Foo() {
    this.a = 1;
}

function Bar() {
    this.c = 3;
}

Foo.prototype.b = 2;
Bar.prototype.d = 4;

console.log(Object.getOwnPropertyDescriptors(Foo));
console.log(Object.getOwnPropertyDescriptors(Bar));
console.log(Object.getOwnPropertyDescriptors(new Foo));
console.log(Object.getOwnPropertyDescriptors(new Bar));

let obj = _.assign({'a': 0}, new Foo, new Bar);
console.log(obj);
