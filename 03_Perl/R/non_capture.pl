
#!/usr/bin/env perl -w


# 通常捕获

$_ = "saurus steak";
if (/(bronto)?saurus (steak|burger)/) {
    print "Fred wants a $2\n";
}

$_ = "bronto saurus burger";
if (/(bronto)?saurus (steak|burger)/) {
    print "Fred wants a $2\n";
}


# 不捕获模式

$_ = "saurus steak";
if (/(?:bronto)?saurus (steak|burger)/) {
    print "Fred wants a $1\n";
}

$_ = "bronto saurus burger";
if (/(?:bronto)?saurus (steak|burger)/) {
    print "Fred wants a $1\n";
}