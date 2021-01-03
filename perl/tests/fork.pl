
#!/usr/bin/env perl

use strict;
use warnings;

if (!defined(my $pid = fork())) {
    die "fork failed: $!\n";
} elsif ($pid == 0) {
    my $subpid = $$;
    print "in child process, process id is $subpid\n";
    sleep(3);
    exec("date") || die "exec 'date' failed: $!\n";
    print "could not reach here\n"
} else {
    print "in parent process, and child process id is $pid\n";
    my $ret = waitpid($pid, 0);     # 等待子进程退出
    printf "child process executed over. ret=$ret\n"
}