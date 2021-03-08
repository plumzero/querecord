
### metatable 和 metamethod

Lua 中的每个值都有一个 metatable 。metatable 是一种普通的 Lua table，用于定义执行特定操作时这个值所表现出的行为。

接下来，让我们深入 metatable 去了解...

程序员可以通过设置 metatable 中的特定域(field)来改变相应的操作行为。比如，当 non-number 类型值作为加法操作符的操作数时，Lua 会去 metatable 中寻找 "__add" 域。"__add" 是一个函数，如果找到了，Lua 就会调用并执行相应操作。

metatable 中的 key 的形式为 "__事件名"，与此对应的值称为 metamethod 。上例中，"__add" 是一个 key ，"__add" 所对应的值就是其所表现出的行为。

table 和 full userdata 类型的每个值都有自己的 metatable(这些 metatable 可以在它们之间共享)。其他类型的值共享一个对应的 metatable ，即一个 metatable 用于所有的 number 值，一个 metatable 用于所有的 string 值，等等。

metatable 控制每个对象如何进行算术操作、位操作、顺序比较、连接、长度操作、调用以及索引操作等。

| 事件域 | 事件行为 |
|:-------|:---------|
| __add  | 加法     |
| __sub  | 减法     |
| __mul  | 乘法     |
| __div  | 欧氏除法 |
| __mod  | 取余     |
| __pow  | 幂乘     |
| __unm  | 否定     |
| __idiv | floor 除法 |
| __band | 位与操作 |
| __bor  | 位或操作 |
| __bxor | 异或操作 |
| __bnot | 位反操作 |
| __shl  | 位左移   |
| __shr  | 位右移   |
| __concat | 连接   |
| __len  | 获取长度 |
| __eq   | 等号     |
| __lt   | 小于     |
| __le   | 小于等于 |
| __index | 对 table 的索引访问 |
| __nexindex | 对 table 的索引对应值的更新 |
| __call | 调用     |

__call 调用形式为 `func(args)`。这里的 func 并不是一个函数，而是一个 non-function 类型的值。Lua 会去 func 中寻找事件域为 __call 的 metamethod。如果存在，就会通过 args 进行调用。
```lua
    mytable = {};
    newtable = { 10, 20, 30 };
```
__call 是唯一一个允许多返回值的 metamethod 。
 

### getmetatable 和 setmetatable 函数

程序员可以通过 `getmetatable` 函数来引用任何类型值的 metatable。

程序员可以通过 `setmetatable` 函数来替换 table 类型的 metatable，但也只仅限于 table 类型。

