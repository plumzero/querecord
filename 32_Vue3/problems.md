


### P1

```sh
    Watchpack Error (watcher): Error: ENOSPC: System limit for number of file watchers reached,
```

在 shell 会话中执行如下命令:
```sh
    sysctl fs.inotify.max_user_watches=524288
```

### P2

```sh
error  Component name "Home" should always be multi-word  vue/multi-word-component-names
```

`.vue` 组件命名时，这样命名 `Home.vue` 是错误的，这样命名 `MyHome` 是正确的。

或者在 vue.config.js 配置中添加 `lintOnSave: false`，变为:
```js
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave: false
})
```

### P3

在 '@vue/cli 5.0.6' 中 create 的工程，在 '@vue/cli 5.0.8' 中执行 'npm run serve' 报错如下:
```sh
> helloworld@0.1.0 serve /path/to/helloworld
> vue-cli-service serve

sh: 1: vue-cli-service: not found
npm ERR! code ELIFECYCLE
npm ERR! syscall spawn
npm ERR! file sh
npm ERR! errno ENOENT
npm ERR! helloworld@0.1.0 serve: `vue-cli-service serve`
npm ERR! spawn ENOENT
npm ERR! 
npm ERR! Failed at the helloworld@0.1.0 serve script.
npm ERR! This is probably not a problem with npm. There is likely additional logging output above.
npm WARN Local package.json exists, but node_modules missing, did you mean to install?

npm ERR! A complete log of this run can be found in:
npm ERR!     /root/.npm/_logs/2022-07-19T02_20_26_731Z-debug.log
```
这个错误和 vue 版本无关，是因为没有 node_modules 依赖目录。执行 `npm install` 就可以了。

