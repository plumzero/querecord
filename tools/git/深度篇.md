
### 参考
- [Git深度使用经验总结](https://blog.csdn.net/a13271785989/article/details/42777893)

### 子模块
- 首次将某个分支作为子模块添加到项目中
  ```shell
    git submodule add -b revert-236-master git@github.com:oktal/pistache.git
  ```
- 重新克隆项目后，默认子模块目录无任何内容，执行这个拉取子模块
  ```shell
    git submodule update --init --recursive
  ```
- 子模块提交更新后，使用子模块的项目必须手动更新才能包含最新的提交
  ```shell
    git submodule foreach git pull
  ```
- 子模块维护地址发生变化，或者需要替换子模块，就需要删除原有的子模块
  ```shell
    rm -rf 子模块目录        ## 删除子模块目录及源码
    vi .gitmodules          ## 删除项目目录下 .gitmodules 文件中子模块相关条目
    vi .git/config          ## 删除配置项中子模块相关条目
    rm .git/module/*        ## 删除模块下的子模块目录，每个子模块对应一个目录，注意只删除对应的子模块目录即可
  ```
  执行完成后，再执行添加子模块命令即可，如果仍然报错，执行如下：
  ```shell
    git rm --cached 子模块名称
  ```
  完成删除后，提交到仓库即可。

### 删除远程仓库自某个提交开始之后的提交
- 假如有四次 commit, 其id(按时间由近到远排序)如下:
  ```shell
    3a762960dee
    470854039cb
    4b7502dbfd3
    39b2d73f309
  ```
  现在要删除 `4b7502dbfd3` 之后的所有提交(即 `470854039cb` 和 `3a762960dee`)，可以这样操作:
  ```shell
    git reset --hard 4b7502dbfd3
    git push -f
  ```
  注意: 该操作不可挽回(工作区将会回滚到提交 `4b7502dbfd3` 后的状态，在 `4b7502dbfd3` 之后的修改不会保存，这之后的提交也无法找回)，谨慎使用。
- 如果想撤销 `4b7502dbfd3` 之后的提交并产生一次新的提交，但 `4b7502dbfd3` 之后的历史提交也想保留在提交历史中，可以这样操作:
  ```shell
    git revert 4b7502dbfd3
  ```

### 在历史提交上新建分支并在此分支上保留该历史提交之后的修改

- 假如有四次 commit, 其id(按时间由近到远排序)如下:
  ```shell
    3a762960dee
    470854039cb
    4b7502dbfd3
    39b2d73f309
  ```
  现在想在 `470854039cb` 上分出一个 branch，但同时想要保留在这之后的修改，可以这样操作:
  ```shell
    git branch new_branch
    git checkout new_branch
    git reset 470854039cb
  ```
  此时，new_branch 的 HEAD 是 `470854039cb`，同时在 HEAD 之后的修改得以保留(工作区有文件待 add)。

### 替换本地改动
- 将本地改动过的追踪文件替换为 HEAD 中的内容
  ```sh
    git checkout -- certain_filename
    git checkout -- *
  ```
- 丢弃所有本地改动过的追踪文件(也就是使用本地最新提交 HEAD 替换这些文件)
  ```sh
    git reset --hard
  ```
- 丢弃所有本地改动过的追踪文件与只存在于本地的提交，拉取远程服务器上的最近提交替换之
  ```sh
    git fetch origin
    git reset --hard origin/master
  ```
  
  

