
#!/usr/bin/env perl

$PATH = "hello perl";

system('echo $PATH');		# $PATH 作为 shell 环境变量
system("echo $PATH");		# $PATH 作为 perl 变量
system("echo \$PATH");		# 转义 $
