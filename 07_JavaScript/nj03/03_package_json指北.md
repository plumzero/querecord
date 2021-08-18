
什么是 package.json 呢？

`package.json` 像工程清单一样。它可以做很多事情，事情之间可以互不关联。它也可以作为工具的存储配置，比如 npm 和 yarn 就将安装包的名称和版本记录在这里。

### 文件结构

一个空的 package.json 文件:
```json
    {}
```
关于 package.json 里面必须有什么没有固定的要求，唯一的要求就是它必须是 json 格式。

如果你创建了一个 Node.js 包，并想通过 npm 实现分发，这个时候你就必须保证 package.json 中会存在一些让他人能够明白怎么使用的属性。这个后面再说。

再看一个文件:
```json
    {
        "name": "test-project"
    }
```
定义了一个 `name` 属性，告知了应用或包的名称。

还有更复杂的，从 Vue.js 上提出来的示例:
```json
    {
        "name": "test-project",
        "version": "1.0.0",
        "description": "A Vue.js project",
        "main": "src/main.js",
        "private": true,
        "scripts": {
            "dev": "webpack-dev-server --inline --progress --config build/webpack.dev.conf.js",
            "start": "npm run dev",
            "unit": "jest --config test/unit/jest.conf.js --coverage",
            "test": "npm run unit",
            "lint": "eslint --ext .js,.vue src test/unit",
            "build": "node build/build.js"
        },
        "dependencies": {
            "vue": "^2.5.2"
        },
        "devDependencies": {
            "autoprefixer": "^7.1.2",
            "babel-core": "^6.22.1",
            "babel-eslint": "^8.2.1",
            "babel-helper-vue-jsx-merge-props": "^2.0.3",
            "babel-jest": "^21.0.2",
            "babel-loader": "^7.1.1",
            "babel-plugin-dynamic-import-node": "^1.2.0",
            "babel-plugin-syntax-jsx": "^6.18.0",
            "babel-plugin-transform-es2015-modules-commonjs": "^6.26.0",
            "babel-plugin-transform-runtime": "^6.22.0",
            "babel-plugin-transform-vue-jsx": "^3.5.0",
            "babel-preset-env": "^1.3.2",
            "babel-preset-stage-2": "^6.22.0",
            "chalk": "^2.0.1",
            "copy-webpack-plugin": "^4.0.1",
            "css-loader": "^0.28.0",
            "eslint": "^4.15.0",
            "eslint-config-airbnb-base": "^11.3.0",
            "eslint-friendly-formatter": "^3.0.0",
            "eslint-import-resolver-webpack": "^0.8.3",
            "eslint-loader": "^1.7.1",
            "eslint-plugin-import": "^2.7.0",
            "eslint-plugin-vue": "^4.0.0",
            "extract-text-webpack-plugin": "^3.0.0",
            "file-loader": "^1.1.4",
            "friendly-errors-webpack-plugin": "^1.6.1",
            "html-webpack-plugin": "^2.30.1",
            "jest": "^22.0.4",
            "jest-serializer-vue": "^0.3.0",
            "node-notifier": "^5.1.2",
            "optimize-css-assets-webpack-plugin": "^3.2.0",
            "ora": "^1.2.0",
            "portfinder": "^1.0.13",
            "postcss-import": "^11.0.0",
            "postcss-loader": "^2.0.8",
            "postcss-url": "^7.2.1",
            "rimraf": "^2.6.0",
            "semver": "^5.3.0",
            "shelljs": "^0.7.6",
            "uglifyjs-webpack-plugin": "^1.1.1",
            "url-loader": "^0.5.8",
            "vue-jest": "^1.0.2",
            "vue-loader": "^13.3.0",
            "vue-style-loader": "^3.0.1",
            "vue-template-compiler": "^2.5.2",
            "webpack": "^3.6.0",
            "webpack-bundle-analyzer": "^2.9.0",
            "webpack-dev-server": "^2.9.1",
            "webpack-merge": "^4.1.0"
        },
        "engines": {
            "node": ">= 6.0.0",
            "npm": ">= 3.0.0"
        },
        "browserslist": ["> 1%", "last 2 versions", "not ie <= 8"]
    }
```
这里有很多需要值得注意的属性字段:
* `version`: 当前版本
* `name`: 应用/包的名称
* `description`: 关于应用/包的简介
* `main`: 应用的入口
* `private`: 为 `true` 时防止应用/包在 npm 上被不小心发布
* `scripts`: 定义了可以运行的一些 node 脚本
* `dependencies`: 通过 npm 安装的依赖包
* `devDependencies`: 通过 npm 安装的开发依赖包
* `engines`: 应用/包所使用的 Node.js 版本
* `browserslist`: 告知支持的浏览器版本


### 细述属性

一一讲述上面所提到的属性。

#### name

设置包的名称。
```json
    "name": "test-project"
```
必须少于 214 个字符，禁用空白符，只允许小写和使用连字符 `-` 或下划线 `_`。

#### author

设置包的作者信息。
```json
    {
        "author": "Joe <joe@whatever.com> (https://whatever.com)"
    }
```
也可以这样:
```json
    {
        "author": {
            "name": "Joe",
            "email": "joe@whatever.com",
            "url": "https://whatever.com"
        }
    }
```

#### contributors

列出贡献者信息，数组形式:
```json
    {
        "contributors": ["Joe <joe@whatever.com> (https://whatever.com)"]
    }
```
也可以这样:
```json
    {
        "contributors": [
            {
            "name": "Joe",
            "email": "joe@whatever.com",
            "url": "https://whatever.com"
            }
        ]
    }
```

#### bugs

设置问题追踪链接路径，有点类似 GitHub issues 页:
```json
    {
        "bugs": "https://github.com/whatever/package/issues"
    }
```

#### homepage

设置包的主页。
```json
    {
        "homepage": "https://whatever.com/package"
    }
```

#### version

指示包的当前版本。
```json
    "version": "1.0.0"
```
遵循版本标记语法 `x.x.x`，分别表示主版本号、次版本号和补丁版本号。

#### license

指示包的许可证。
```json
    "license": "MIT"
```

#### keywords

关联一组这个包的用途的关键字。
```json
    "keywords": [
        "email",
        "machine learning",
        "ai"
    ]
```
使用者可以根据这些关键字在 npm 上查找类似功能的包。

#### description

包的简介。
```json
    "description": "A package to work with strings"
```

#### repository

指出包的仓库位置。
```json
    "repository": "github:whatever/testing",
```
也可以这样:
```json
    "repository": {
        "type": "git",
        "url": "https://github.com/whatever/testing.git"
    } 
```

#### main

设置包的入口点。
```json
    "main": "src/main.js"
```

#### private

如果设置为 `true` ，可以避免包在 npm 上被不小心发布。
```json
    "private": true
```

#### scripts

定义可运行的一组 node 脚本。
```json
    "scripts": {
        "dev": "webpack-dev-server --inline --progress --config build/webpack.dev.conf.js",
        "start": "npm run dev",
        "unit": "jest --config test/unit/jest.conf.js --coverage",
        "test": "npm run unit",
        "lint": "eslint --ext .js,.vue src test/unit",
        "build": "node build/build.js"
    }
```
你可以通过 `npm run xxxx` 或者 `yarn xxxx` 进行调用，`xxxx` 是命令的名称，比如 `npm run dev` 。

#### dependencies

列出包所依赖的 npm 包。

当你执行如下的命令时:
```bash
    npm install <package-name>
    yarn add <package-name>
```
这些包名会自动被添加到这个列表中去。比如:
```json
    "dependencies": {
        "vue": "^2.5.2"
    }
```

#### devDependencies

列出所依赖的开发依赖 npm 包。

与 dependencies 不同，devDependencies 只需要安装在开发环境上，在运行环境中则不作要求。

当你执行如下的命令时:
```bash
    npm install --save-dev <PACKAGENAME>
    yarn add --dev <PACKAGENAME>
```
这些包名会自动被添加到这个列表中去。比如:
```json
    "devDependencies": {
        "autoprefixer": "^7.1.2",
        "babel-core": "^6.22.1"
    }
```

#### engines

设置包工作的 Node.js 版本。
```json
    "engines": {
        "node": ">= 6.0.0",
        "npm": ">= 3.0.0",
        "yarn": "^0.13.0"
    }
```

#### browserslist

告知他人包支持的浏览器版本。
```json
    "browserslist": [
        "> 1%",
        "last 2 versions",
        "not ie <= 8"
    ]
```

