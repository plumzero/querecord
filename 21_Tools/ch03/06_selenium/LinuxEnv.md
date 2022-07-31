
### 说明

安装与测试环境:
```shell
	VMware Pro
	RHEL 7.5
	Python 3
```

安装包:
```shell
	selenium-3.141.0.tar.gz
	geckodriver-v0.24.0-linux64.tar.gz
```


### Selenium 的配置

解压
```shell
    tar -zxvf selenium-3.141.0.tar.gz
```

生成库
```shell
    cd selenium-3.141.0
    python seup.py install
```
在当前目标下会生成一个 build/lib, 里面应该是 selenium 所需要的库，接下来应该需要对其进行配置，但配置方法暂时未知 ...

### geckodriver 的配置

解压
```shell
    tar -zxvf geckodriver-v0.24.0-linux64.tar.gz
```

配置。解压出一个可执行文件`geckodriver`，将此文件移动到命令搜索目录下即可:
```shell
    mv geckodriver /usr/bin/
```

其他配置:
1. linux 还需要安装 firefox 浏览器。由于本测试 linux 未安装图形化界面，所有暂时还不知道下一步该怎么办。
2. 不成功的配置，有机会再试试...
