
### 查看已安装 npm 包的版本

命令必须在工程路径下执行。
```bash
    npm list
    npm list --depth=0      # 指定深度
    npm list cowsay         # 根据依赖包名查看
    npm view cowsay version # 简查
```
当然，也可以从 package-lock.json 中查看。

查看全局:
```bash
    npm list -g
```


### 安装老版本的 npm 包

通过 `@` 语法指定要安装的老版本:
```bash
    npm install <package>@<version>
```

比如:
```bash
    npm install cowsay@1.2.0
```

同样地，也对全局有效:
```bash
    npm install -g webpack@4.16.4
```

不知道老的版本号有哪些？通过这个查看:
```bash
    npm view cowsay versions
```


### 将所有依赖更新到最新

当你使用 `npm install <package-name>` 时，安装的就是最新的依赖，相应的依赖条目也会被添加到 package.json 和 package-lock.json 中去。

通过 `npm update` 可以更新依赖包，同时更新的还有 package-lock.json。5.0.0 版本以后，npm update 默认还会对 package.json 进行更新，可以通过 `npm update --no-save` 避免对 package.json 的修改。

通过 `npm outdated` 可以发现依赖包最新的版本。

npm update 只会对小版本号或者补丁版本号变化的包进行更新，不会对大版本号变化的包进行更新，因为大版本号的变化往往意味着依赖包有了突破性的变动，npm 对这种变化持谨慎态度。

`npm install` 通过 `npm-check-updates` 参数对大版本号进行更新，(其实看起来更像是重装了╮(╯▽╰)╭):
```bash
    npm install -g npm-check-updates
```
之后运行:
```bash
    ncu -u
```

### npm 包版本语义

了解 npm 包版本的语义很重要，因为全网都要遵守。

[参考](https://nodejs.dev/learn/semantic-versioning-using-npm)


### 卸载依赖包

在所在工程下卸载局部包:
```bash
    npm uninstall <package-name>
```
指定 `-S` 或 `--save` 标识时，会同时移除 package.json 中涉及到的相关信息，主要是 `devDependency` 和 `dependency` 属性字段。

卸载全局包:
```bash
    npm uninstall -g <package-name>
```
