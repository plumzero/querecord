
#!/usr/bin/env perl -wait

{
    my $filename = "/etc/passwd";
    print "$filename exist\n" if -e $filename;
}

{
    my $filename = "/etc/passwd";
    warn "Config file is looking pretty old!\n"
        if -M $filename > 28;
}

{
    chomp(my @bootlogs = `ls /var/log/boot*`);
    
    foreach (@bootlogs) {
        print "$_ 大于 12KB 且已经有 1 天没有被访问过了.\n"
            if -s $_ > 12000 and -A $_ > 1; 
    }
}
