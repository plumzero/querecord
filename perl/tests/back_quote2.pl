
#!/usr/bin/env perl -w

use strict;

my @files = `ls -l`;
foreach my $a (@files) {
    print $a;
}

foreach (my $a = `ls -l`) {
    print $a;
}

foreach (`ls -l`) {
    print $_;
}

foreach (`ls -l`) {
    my($mask,$time,$name) = /(\S+)\s+.*([\d]{2}:[\d]{2})\s+(.*)/;
    print "mask=$mask time=$time name=$name\n";
}