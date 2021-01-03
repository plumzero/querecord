
#!/usr/bin/env perl -w

$_ = "a real \\ backslash";

if (/\\/) {
    print "It matched!\n";
}