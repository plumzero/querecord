
### Babel 功能模块

1. babel-node

此命令提供一个支持 ES6 的 REPL 环境，在 REPL 环境下可以定义和运行变量、函数、对象。它支持 Node 的 REPL 环境的所有功能，还可直接运行 ES6 代码。

其在项目下的安装方法:
```js
    npm install --save-dev @babel/node
```

执行 babel-node 可以进入 REPL 环境，也可以直接运行脚本。

要想成功使用 REPL 环境，babel 的所有包必须版本一致。如果由于包版本不一致出现报错，解决办法就是用以下命令对包进行全部升级:
```js
    npx babel-upgrade --write --install
```

2. @babel/register

利用此模块可以无需手动转码(ES6 转 ES5)，当使用 require 进行加载 .js .jsx .es 和 .es6 后缀名的文件，就会先用 Babel 进行转码。

在使用时，必须首先加载 `@babel/register`。
