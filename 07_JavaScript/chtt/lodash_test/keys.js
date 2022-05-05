
import _ from 'lodash';

// _.keys(object)

// 创建一个 object 的自身可枚举属性名为数组。

// 注意: 非对象的值会被强制转换为对象。

// 参数:
//  object: 要检索的对象

// 返回
//  返回包含属性名的数组

function Foo() {
    this.a = 1;
    this.b = 2;
}

Foo.prototype.c = 3;

console.log(_.keys(new Foo));

console.log(_.keys('hi'));
