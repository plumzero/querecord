
import _ from 'lodash';

// _.assignIn(object, [sources])

// 这个方法类似 _.assign，除了它会遍历并继承来源对象的属性。

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

let obj = _.assignIn({'a': 0}, new Foo, new Bar);
console.log(obj);

Bar.prototype.d = 5;
Bar.prototype.e = 6;
let o = _.assignIn(obj, new Bar);
console.log(o);
