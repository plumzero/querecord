
### 说明

安装与测试环境:
```shell
	Python 3
```

安装包:
```shell
	python-3.7.2.exe
	geckodriver-v0.20.0-win64.zip
```


### Python3 在 Windows 上的的安装与配置

1. 点击安装 python-3.7.2.exe，安装到合适目录即可

2. 配置 python 环境变量。

  这里将 python 配置为系统变量。为方便后续 selenium 的安装，还需要配置 pip(Python3.x 安装后默认有 pip)。

  python 的配置
  ```shell
		D:\Users\lb\AppData\Local\Programs\Python\Python37-32\
  ```
  pip 的配置
  ```shell
    D:\Users\lb\AppData\Local\Programs\Python\Python37-32\Scripts\
  ```


### Selenium 的配置

1. python 配置完成后在 windows 命令行通过 pip 执行 selenium 的安装
  ```shell
    pip install selenium
  ```
2. 查看安装结果
  ```shell
    pip show selenium
  ```
3. 本例中，通过 pip 安装的包都在 `D:\Users\lb\AppData\Local\Programs\Python\Python37-32\Lib\site-packages\` 目录下

### geckodriver 的配置

1. 解压后得到一个可执行命令，将其配置为系统环境变量
   ```shell
     C:\Command\firefox\
   ```


### 测试

```py
	from selenium import webdriver
	driver = webdriver.Firefox()
	driver.get("http://cn.bing.com/")
	driver.find_element_by_id("sb_form_q").send_keys("WebDriver")
	driver.find_element_by_id("sb_form_go").click()
	driver.quit()
```


### windows 下可能还需要安装的包

看测试目的
```shell
	pip install pyyaml
	pip install xlrd
```
