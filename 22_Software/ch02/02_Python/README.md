
### 安装 python3

- 安装环境

    VMware version:         14.1.1
    linux kernel version:   3.10.0-862.el7.x86_64
    Linux Release:          RedHat 7.5
    Lua version:            Python-3.8.5

- 解压 tarball 进入顶层目录下
  ```sh
    tar -Jxvf Python-3.8.5.tar.xz
    cd Python-3.8.5
  ```

- 配置
  ```sh
    ./configure --prefix=/usr/local/python
  ```
  指定安装到 `/usr/local/python` 目录下。

- 编译、测试与安装
  ```sh
    make
    make install
  ```

- 软链，以便后续使用
  ```sh
    ln -s /usr/local/python/bin/python3.8 /usr/bin/python3
  ```


### 为 python3 安装 pip3(Python Package Installer)

也可以通过 `yum install python3-pip` 来安装 pip3，这是源安装完成之后才发现的...

- 安装版本
  ```
    pip-20.2.4
  ```
  
- 依赖安装(useful for apt-get/yum)
  
  注意: 应该安装与 python3 相关的 setuptools, 可以通过 `yum search setuptools` 查看，输出如下:
  ```sh
    python-setuptools.noarch : Easily build and distribute Python packages
    python3-setuptools.noarch : Easily build and distribute Python 3 packages
  ```
  选择 `python3-setuptools` 进行安装。
  ```sh
    yum install python3-setuptools
  ```
 
- 解压
  ```sh
    tar -zxvf pip-20.2.4.tar.gz
    cd pip-20.2.4
  ```

- 安装
  ```sh
    python3 setup.py install
  ```
