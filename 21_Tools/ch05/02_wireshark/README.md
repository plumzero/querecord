
### ubuntu 16.04 下安装/使用 wireshark

安装 wireshark:
```s
    sudo apt-get install wireshark
```

新建 wireshark 用户组，把当前用户加入 wireshark 用户组:
```s
    sudo groupadd wireshark
    sudo chgrp wireshark /usr/bin/dumpcap
    sudo chmod 4755 /usr/bin/dumpcap
    sudo gpasswd -a fangyi wireshark
```
第一条命令是新建 wireshark 用户组，二、三条命令是配置和添加权限。第四条命令中的 fangyi 是当前系统的用户名。

在命令行中输入 wireshark 就可以打开，然后选择你的网卡名称(如 enp2s0)。

