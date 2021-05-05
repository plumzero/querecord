
## GRUB 和 GRUB2
- RHEL 7 系统采用 GRUB2 引导加载程序，
- 截至到 ubuntu 16.04 和 debian 9.8.0, 仍使用 GRUB 引导加载程序，其后版本为知。

## GRUB 2主配置文件
- GRUB 2 的配置通过以下三个地方的文件来完成：
    + /boot/grub2/grub.cfg (/etc/grub2.cfg 文件是 /boot/grub2/grub.cfg 文件的软链接)
    + /etc/grub.d 目录
    + /etc/default/grub (/etc/sysconfig/grub 文件是 /etc/default/grub 文件的软链接)
    + 它们的关系是在 /boot/grub2/grub.cfg 文件里面通过 "### BEGIN   ###" 这种格式按
    照顺序调用 /etc/grub.d 目录中的脚本实现不同的功能。而这些脚本又会调用 /etc/default/grub
    配置文件来实现相应的启动配置。
- 修改配置步骤
    + 不要直接去修改 /boot/grub2/grub.conf 文件；
    + 通过修改 /etc/grub.d 目录下的脚本或者 /etc/default/grub 文件修改配置；
    + 使用 grub2-mkconfig 命令重新生成 /boot/grub2/grub.cfg 文件；
            grub-mkconfig -o /boot/grub/grub.cfg
- grub.cfg 关键字说明
    + menuentry: 菜单项，rhel7.5 中有两个选项，一个是普通模式，一个是救援模式；
- 与 debian 系列(使用 GRUB)的差异
    + GRUB 使用 grub-mkconfig 命令重新生成 /boot/grub/grub.cfg 文件；
    + GRUB 没有 /boot/grub2 目录，而是 /boot/grub 目录；
    + GRUB 在 /etc 目录下没有 /boot 目录下相关 grub 文件的软链接；
    
## /etc/grub.d 目录脚本说明
	+ 00_header                 设置 grub 默认参数
	+ 10_linux                  系统中存在的多个 Linux 版本
	+ 20_ppc_terminfo           设置 tty 控制台
	+ 30_os_prober              设置其他分区中的系统(硬盘中有多个操作系统时设置)
	+ 40_custom 和 41_custom    用户自定义的配置

## /etc/default/grub 文件详解
    GRUB_TIMEOUT=5
        设置进入默认启动项的等候时间，默认值 5 秒，-1 表示无限等待。
    GRUB_DISTRIBUTOR="$(sed 's, release .*$,,g' /etc/system-release)"
        由 GRUB 发布者设置他们的标识名，这用于产生更具信息量的菜单项名称。
    GRUB_DEFAULT=saved
        设置默认启动项。比如要默认从第 1 个菜单项启动，设置为 0。要默认从第 2 个菜
        单项启动，设置为 1。如果设置为 saved, 则默认为上次启动项。
        rhel7 默认为 saved, debian 和 ubuntu 默认为 0 。
    GRUB_TERMINAL_OUTPUT="console"
        选择终端输出设备，多个设备时用空格分开。有效的终端输出名依赖于平台，这可能
        包括 console(PC BIOS 及 EFI 控制台)、 serial(串行终端)、gfxterm(图形模式输
        出)、 ofconsole(开放固件控制台)或 vga_text(VGA 文本输出)。
        一般为 console 。
    GRUB_CMDLINE_LINUX="crashkernel=auto rhgb quiet"
        手动添加内核启动参数。
    GRUB_DISABLE_RECOVERY="true"
        设置是否启用修复模式。
    GRUB_DISABLE_LINUX_RECOVERY="true"
        (非重要配置)设置是否创建修复模式菜单项。
    GRUB_HIDDEN_TIMEOUT=0
        不显示菜单，但会显示空白界面，设置时间内按任意键出现菜单。
    GRUB_HIDDEN_TIMEOUT_QUIET=true
        显示空白界面时是否出现倒计时。
    GRUB_CMDLINE_LINUX_DEFAULT="quiet"
        添加默认内核启动参数。
        debian/ubuntu 下为 quiet, rhel7.5 下未配置。
    GRUB_TERMINAL=console
        设置使用终端还是图形界面引导。
    GRUB_GFXMODE=640x480
        设置图形界面分辨率。只通使用显卡支持的分辨率。
        可以在 grub 模式下输入 vbeinfo 查看。
    GRUB_DISABLE_LINUX_UUID=true
        设置是否使用 UUID 引导，一般不用。
    GRUB_INIT_TUNE="480 440 1"
        在 GRUB 启动时，调整扬声器的音量。
