
#!/usr/bin/env perl -w

my $dir_to_process = '/etc';

opendir my $dh, $dir_to_process or die "Cannot open $dir_to_process: $!";

foreach my $file (readdir $dh) {
    print "one file in $dir_to_process is $file\n";
}

closedir $dh;
