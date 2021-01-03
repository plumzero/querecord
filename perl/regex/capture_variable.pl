
#!/usr/bin/env perl -w


# 捕获空白符和逗号之间的单词

$_ = "Hello there, neighbor";
if (/\s([a-zA-Z]+),/) {
    print "the word was $1\n";
}


# 捕获多个字符串

$_ = "Hello there, neighbor";
if (/(\S+) (\S+), (\S+)/) {
    print "the word was $1 $2 $3\n";
}


my $dino = "I fear that I'll be extinct after 1000 years.";
if ($dino =~ /([0-9]*) years/) {
    print "That said '$1' years.\n";
}