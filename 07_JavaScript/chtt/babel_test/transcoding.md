
### 安装 babel

安装 babel:
```js
    npm init -y
    npm install --save-dev @babel/core
```

安装 babel 转义器(二选一):

使用最新转码规则
```js
    npm install --save-dev @babel/preset-env
```

react 转码规则
```js
    npm install --save-dev @babel/preset-react
```


### 配置 .babelrc

在项目中创建配置文件 `.babelrc`:
```js
    touch .babelrc
```

配置文件 `.babelrc`。人工输入如下内容:
```js
    {
        "presets": [],
        "plugins": []
    }
```

将安装的转码规则加入到 .babelrc 中:
```js
    {
        "presets": [
            "@babel/preset-env"
        ],
        "plugins": []
    }
```


### 测试

在当前目录下创建一个测试目录，这里是 src，创建一个 example.js 测试文件。

将代码 `"build": "babel src -d lib"` 添加到 package.json 文件中的 `scripts` 属性名中，这里添加后的结果为:
```js
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build": "babel src -d lib"
  }
```

在项目内安装命令行工具用于命令行转码:
```js
    npm install --save-dev @babel/cli
```
不能使用全局的。

尝试转码:
```js
    npm run build
```

也可以使用如下转码方法:
```js
    # 转码结果输出到标准输出
    npx babel src/example.js

    # 转码结果写入一个文件
    npx babel example.js --out-file compiled.js
    # 或者
    npx babel example.js -o compiled.js

    # 整个目录转码
    npx babel src --out-dir lib
    # 或者
    npx babel src -d lib

    # -s 参数生成 source map 文件
    npx babel src -d lib -s
```
