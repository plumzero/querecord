


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
