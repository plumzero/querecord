
### perf 的安装

在控制台执行 perf 命令，如果没有安装，会输出如下信息:
```sh
The program 'perf' is currently not installed. You can install it by typing:
apt install linux-tools-common
```

根据输出提示执行如下命令:
```sh
    apt install linux-tools-common
```

查看版本:
```sh
    perf --version
```
如果输出如下信息:
```sh
WARNING: perf not found for kernel 4.4.0-186

  You may need to install the following packages for this specific kernel:
    linux-tools-4.4.0-186-generic
    linux-cloud-tools-4.4.0-186-generic

  You may also want to install one of the following packages to keep up to date:
    linux-tools-generic
    linux-cloud-tools-generic
```

尝试执行如下命令:
```sh
    apt-get install linux-tools-4.4.0-186-generic
```

再次查看版本:
```sh
    perf version 4.4.228
```

