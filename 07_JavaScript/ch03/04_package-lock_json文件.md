
5 版本之后，npm 引入了 `package-lock.json` 文件。

这个文件的目标是对每个安装的依赖包的版本保持准确的追踪，这样就可以保证产品或项目 100% 可复原。

package-lock.json 也是对 package.json 遗留问题的补漏。在 package.json 文件中你可以设置你想要的更新(补丁或镜像)，例如:
* 如果是 `~0.13.0`，则可以更新为 `0.13.1`，但不能更新为 `0.14.0`。
* 如果是 `^0.13.0`，则可以完成 `0.13.1`、`0.13.2` 等类似更新。如果是 `^1.13.0`，则可以完成 `1.13.1`、`1.14.0`、`2.0.0` 等类似更新。
* 如果是 `0.13.0`，则只能完成 `0.13.0` 这一种更新。

我们一般不会将 node_modules 提交到 Git，因为这可能会很大。当你想要从另一台机器上通过 `npm install` 指令复制整个项目时，如果这时使用了 `~` 语法，那么这很可能导致下载的依赖包与原版不一致。

这就造成了原始项目与新初始化的项目不一致，即使是一个小版本号、甚至一个补丁号的不同，也可能产生不一致的效果。

`package-lock.json` 使当前安装的每个包的版本固定不变，这样 npm 就可以通过 `npm install` 准确地下载到一样的版本。

因此 `package-lock.json` 文件需要提交到你的仓库上，以便其他人可以获取并据此执行想要的操作。

需要注意的是，当执行 `npm update` 指令时会更新 package-lock.json 文件。

### 示例

比如运行 `npm install cowsay` 后其 package-lock.json 内容如下:
```json
    {
        "requires": true,
        "lockfileVersion": 1,
        "dependencies": {
            "ansi-regex": {
                "version": "3.0.0",
                "resolved": "https://registry.npmjs.org/ansi-regex/-/ansi-regex-3.0.0.tgz",
                "integrity": "sha1-7QMXwyIGT3lGbAKWa922Bas32Zg="
            },
            "cowsay": {
                "version": "1.3.1",
                "resolved": "https://registry.npmjs.org/cowsay/-/cowsay-1.3.1.tgz",
                "integrity": "sha512-3PVFe6FePVtPj1HTeLin9v8WyLl+VmM1l1H/5P+BTTDkMAjufp+0F9eLjzRnOHzVAYeIYFF5po5NjRrgefnRMQ==",
                "requires": {
                    "get-stdin": "^5.0.1",
                    "optimist": "~0.6.1",
                    "string-width": "~2.1.1",
                    "strip-eof": "^1.0.0"
                }
            },
            "get-stdin": {
                "version": "5.0.1",
                "resolved": "https://registry.npmjs.org/get-stdin/-/get-stdin-5.0.1.tgz",
                "integrity": "sha1-Ei4WFZHiH/TFJTAwVpPyDmOTo5g="
            },
            "is-fullwidth-code-point": {
                "version": "2.0.0",
                "resolved": "https://registry.npmjs.org/is-fullwidth-code-point/-/is-fullwidth-code-point-2.0.0.tgz",
                "integrity": "sha1-o7MKXE8ZkYMWeqq5O+764937ZU8="
            },
            "minimist": {
                "version": "0.0.10",
                "resolved": "https://registry.npmjs.org/minimist/-/minimist-0.0.10.tgz",
                "integrity": "sha1-3j+YVD2/lggr5IrRoMfNqDYwHc8="
            },
            "optimist": {
                "version": "0.6.1",
                "resolved": "https://registry.npmjs.org/optimist/-/optimist-0.6.1.tgz",
                "integrity": "sha1-2j6nRob6IaGaERwybpDrFaAZZoY=",

                "requires": {
                    "minimist": "~0.0.1",
                    "wordwrap": "~0.0.2"
                }
            },
            "string-width": {
                "version": "2.1.1",
                "resolved": "https://registry.npmjs.org/string-width/-/string-width-2.1.1.tgz",
                "integrity": "sha512-nOqH59deCq9SRHlxq1Aw85Jnt4w6KvLKqWVik6oA9ZklXLNIOlqg4F2yrT1MVaTjAqvVwdfeZ7w7aCvJD7ugkw==",
                "requires": {
                    "is-fullwidth-code-point": "^2.0.0",
                    "strip-ansi": "^4.0.0"
                }
            },
            "strip-ansi": {
                "version": "4.0.0",
                "resolved": "https://registry.npmjs.org/strip-ansi/-/strip-ansi-4.0.0.tgz",
                "integrity": "sha1-qEeQIusaw2iocTibY1JixQXuNo8=",
                "requires": {
                    "ansi-regex": "^3.0.0"
                }
            },
            "strip-eof": {
                "version": "1.0.0",
                "resolved": "https://registry.npmjs.org/strip-eof/-/strip-eof-1.0.0.tgz",
                "integrity": "sha1-u0P/VZim6wXYm1n80SnJgzE2Br8="
            },
            "wordwrap": {
                "version": "0.0.3",
                "resolved": "https://registry.npmjs.org/wordwrap/-/wordwrap-0.0.3.tgz",
                "integrity": "sha1-o9XabNXAvAAI03I0u68b7WMFkQc="
            }
        }
    }
```
可以看到，cowsay 依赖的包有:
* get-stdin
* optimist
* string-width
* strip-eof

反过来，这些包也会要求对其他包的依赖，这可以在 `requires` 中看到:
* ansi-regex
* is-fullwidth-code-point
* minimist
* wordwarp
* strip-eof

这样依赖包以字母序添加到文件中，每个包都有 `version` 字段、`resolved` 字段(指出包的位置)和 `integrity` 字段(用作包的验证)。
