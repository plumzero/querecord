// 扩展 Foo 以增加新方法
var Foo = (function(FooModule) {
    FooModule.baz = function() {
        console.log(FooModule.bar);
    }

    return FooModule;
}) (Foo || {});

Foo.baz();

// 扩展 Foo 以增加新数据
var Foo = (function(FooModule) {
    FooModule.bar = 'baz';

    return FooModule;
}) (Foo || {});

console.log(Foo.bar);   // 'baz'
Foo.baz();              // 'baz'