
Notepad++ 缺省情况下并不支持 Go 语法高亮，但是我们可以进行配置。

### 语法高亮

代码在[这里](userDefineLang_Go.xml)。

配置步骤如下:

1.运行打开 Notepad++ 。

2.找到菜单栏，依次点击[设置]、下拉菜单中选择[编辑弹出菜单]，这个时候会在 Notepad++ 文件区域打开一个名字为 contextMenu.xml 的文件。当然，这里的目的并不是要修改这个文件，而是根据找到这个文件所在的目录，因为需要对这个目录下的文件进行配置。这里的目录为`%HOME%\AppData\Roaming\Notepad++`，简称为 PATH。

3.进入 PATH 目录下的 `userDefineLangs` 目录，将该目录下的 `userDefinedLang-markdown.default.modern.xml` 文件备份，打开此文件，将上述代码按照格式添加到此文件中。

4.重新运行 Notepad++ 即可。
