// 原始的 Foo
var Foo = (function(bar) {
    var bar = 'baz';

    return {
        bar: bar
    };
}) ();

// 扩展 Foo
var Foo = (function(FooModule) {
    FooModule.baz = function() {
        console.log(FooModule.bar);
    }

    return FooModule;
}) (Foo);

console.log(Foo.bar);   // 'baz'
Foo.baz();              // 'baz'