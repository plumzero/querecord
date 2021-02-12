
## 说明
- Debian9.8 下，普通用户权限下通过 `sudo` 执行程序，输入 root 口令后出现如下报错:
  ```shell
    lb is not in the sudoers file.  This incident will be reported.
  ```

## 解决
- 切换回 root 下
  ```shell
    su -
  ```
- 修改 `/etc/`
  ```shell
	#
	# This file MUST be edited with the 'visudo' command as root.
	#
	# Please consider adding local content in /etc/sudoers.d/ instead of
	# directly modifying this file.
	#
	# See the man page for details on how to write a sudoers file.
	#
	Defaults        env_reset
	Defaults        mail_badpass
	Defaults        secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

	# Host alias specification

	# User alias specification

	# Cmnd alias specification

	# User privilege specification
	root    ALL=(ALL:ALL) ALL
	lb      ALL=(ALL:ALL) ALL

	# Allow members of group sudo to execute any command
	%sudo   ALL=(ALL:ALL) ALL

	# See sudoers(5) for more information on "#include" directives:

	#includedir /etc/sudoers.d
  ```
  在 `root    ALL=(ALL:ALL) ALL` 下加入普通用户名，这里是 `lb      ALL=(ALL:ALL) ALL`
- 保存退出