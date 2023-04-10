

使用 cron 实现任务计划

### 文件说明

- root 用户通过修改 /etc/crontab 文件可以实现任务计划，而普通用户却无法修改文件。
- crond 守护进程可以在无需人工干预的情况下，根据时间和日期的组合来调度执行重复任务。

### 控制 crond 服务

使用 systemctl 命令可以控制 crond 服务。
```s
  systemctl start crond.service           # 启动 crond 服务
  systemctl status crond.service          # 查看 crond 服务状态
  systemctl enable crond.service          # 重新引导系统时自动启动 crond 服务
  systemctl is-enabled crond.service
```

### /etc/crontab 文件详解

```s
        SHELL=/bin/bash
        PATH=/sbin:/bin:/usr/sbin:/usr/bin
        MAILTO=root

        # For details see man 4 crontabs

        # Example of job definition:
        # .---------------- minute (0 - 59)
        # |  .------------- hour (0 - 23)
        # |  |  .---------- day of month (1 - 31)
        # |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
        # |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
        # |  |  |  |  |
        # *  *  *  *  * user-name  command to be executed
```
前 3 行用来配置 cron 任务运行环境的变量。其中:
- SHELL 变量的值告诉系统要使用哪个 shell 环境
- PATH 变量定义用来执行命令的路径
- cron 任务的输出被邮寄给 MAILTO 变量定义的用户名

/etc/crontab 文件中的每一行都代表一项任务，它的格式如下:
```s
  minute   hour   day   month   day of week   user-name   command
```
- minute:      分钟，0~59 之间的任何整数
- hour:        小时，0~23 之间的任何整数
- day:         日期，从 1~31 之间的任何整数（必须为有效日期）
- month:       月份，1~12 之间的任何整数
- day of week: 星期，0~7 之间的任何整数，这里的 0 或 7 代表星期日
- user-name:   执行命令的用户
- command:     要执行的命令或者自己编写的脚本

/etc/crontab 文件配置举例
```s
SHELL=/bin/bash
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root

30 21 * * * root /root/backup.sh
# 在每天晚上的 21:30 执行 /root/backup.sh

45 4 1,10,22 * * root /root/backup.sh
# 在每月 1，10，22日的 4:45 执行 /root/backup.sh 文件

20 1 * * 6,0 root /bin/find -name core -exec rm {} \;
# 在每星期六、星期日的 1:20 执行一个 find 命令，查找相应的文件

0,30 18-23 * * * root /root/backup.sh
# 在每天 18:00~23:00 之间每隔 30 分钟执行 /root/backup.sh

0 23 * * 6 root /root/backup.sh
# 在每星期六的 23:00 执行 /root/backup.sh
```

当使用 cron 运行 shell 脚本时，要由用户来给出脚本的绝对路径，设置相应的环境变量。
    
### /etc/cron.d 目录

- 除了通过修改 /etc/crontab 文件实现任务计划之外，还可以在 /etc/cron.d 目录中创建文件夹来实现。
- 该目录中的所有文件和 /etc/crontab 文件使用一样的配置语法。

### 使用 crontab 命令实现任务计划

- root 以外的用户可以使用 crontab 命令配置 cron 任务。
- 所有用户定义的 crontab 都被保存在 /var/spool/cron 目录中，并使用创建它们的用户身价执行。
- 当前用户通过下列命令打开并编辑自己的 cron 文件:
  ```s
    crontab -e
  ```
  编辑后的 crontab 文件会根据该用户名被保存在 /var/spool/cron/<username> 文件中。
- crobtab 命令语法
  ```s
    crontab [选项]
      选项              选项含义
      -u <用户名>     用户名，如果使用自己的用户名登录，就不需要使用该选项   
      -e              编辑用户的 crontab
      -l              列出用户的 crontab 中的内容
      -r              删除用户的 crontab
  ```

