


### P1

```sh
    Watchpack Error (watcher): Error: ENOSPC: System limit for number of file watchers reached,
```

在 shell 会话中执行如下命令:
```sh
    sysctl fs.inotify.max_user_watches=524288
```

### P2

`.vue` 组件命名时，这样命名 `Demo1.vue` 是错误的，这样命名 `DemoName` 是正确的。
