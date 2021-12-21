
"use strict";

{
    let sym = Symbol();
    console.log(typeof sym);
}

{
    let genericSymbol = Symbol();
    let otherGenericSymbol = Symbol();
    
    let fooSymbol = Symbol('foo');
    let otherFooSymbol = Symbol('foo');
    
    console.log(genericSymbol == otherGenericSymbol);
    console.log(fooSymbol == otherFooSymbol);
}

{
    // let mySymbol = new Symbol();
}

// 全局符号注册表
{
    let fooGlobalSymbol = Symbol.for('foo');        // 创建新符号
    let otherFooGlobalSymbol = Symbol.for('foo');   // 重用已有符号

    console.log(fooGlobalSymbol == otherFooGlobalSymbol);
}

{
    let localSymbol = Symbol('foo');
    let globalSymbol = Symbol.for('foo');

    console.log(localSymbol == globalSymbol);
}

{
    // 创建全局符号
    let s = Symbol.for('foo');
    console.log(Symbol.keyFor(s));

    // 创建普通符号
    let s2 = Symbol('bar');
    console.log(Symbol.keyFor(s2));
}
