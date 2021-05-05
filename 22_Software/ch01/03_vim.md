
### 说明

vim 的全局配置文件是 `/etc/vimrc`，当前用户配置文件是 `~/.vimrc` 。

Uinx 和 Linux 使用 `<LF>` 换行，MacOS 使用 `<CR>` 换行，MS-DOS 和 Windows 使用`<CR><LF>`换行。在 Linux 下用 Vim 查看在 Windows 下编写的文件时，行尾后可能会出现`^M`符号。


### 模式

包括一般模式、编辑模式(又分为插入模式和替换模式)、可视模式、命令模式。这里仅对常用的一般模式的部分使用进行记录。


一般模式常用指令操作:
* 输入`r`然后接着输入某个字母，将替换光标所在位置字母
* `0`	光标移到行首
* `$`	光标移到行尾
* `H`	光标移到屏幕显示第一行
* `L`	光标移到屏幕显示最后一行
* `M`	光标移到屏幕显示中间一行
* 复制
    * 复制一个单词: `y + w`
    * 复制已知连续n行: 1.光标移至起始行: `n键 + yy键`; 2.光标移至要粘贴的前一行: `p键`粘贴
    * 指定连续行复制: `n1,n2 copy n3` 表示将第 n1 行至第 n2 行复制到第 n3 行，copy 换成 move 则为剪切
* 删除
    * 删除指定字符: `x`
    * 删除连续 n 个字符: `n + x`
    * 标记命令完成连续 n 行删除: `'a,'b delete`
    * 删除连续n行: `n + d`
    * 指定连续行删除: `n1,n2 delete`
* 编辑模式下的关键字补全: `Ctrl+N` 和 `Ctrl+P`
* 跳转
    * 光标跳转到命令行的开始部分: `ctrl + a`
    * 光标跳转到命令行的结束部分: `ctrl + e`


### 配色

以 redhat 7.5 为示例。

查看当前 vim 使用配色方案。
通过 vim 打开任意一个文本文件，在 normal 模式下输入`:colorscheme`后可以查看当前使用的配色方案。
  
可以通过 `ls /usr/share/vim/vim74/colors/` 查看 vim 的所有可选配色方案。

向 vim 配置文件末尾写入下列选项更改 vim 配置:
```shell
  syntax on
  set hlsearch
  colorscheme desert
  set nocompatible
  set backspace=indent,eol,start
```

为了使配色方案在 SecureCRT 上生效，需要对后者进行一些配置，步骤如下:
1. Session Options->Terminal->Emulation->Terminal(选择Xterm）并勾选后面的 ANSI Color
2. Session Options->Terminal->Emulation->勾选 Select an alternate keyborad emulation，然后在下拉框中选择 Xterm
3. 重新打开SecureCRT到centos的连接，就可以看到高亮了
