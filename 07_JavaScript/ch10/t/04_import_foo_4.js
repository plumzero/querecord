
import foo, { bar, baz } from './foo.js';
// import { default as foo, bar, baz } from './foo.js';
// import foo, * as Foo from './foo.js';

console.log(bar);
console.log(baz);
console.log(foo);