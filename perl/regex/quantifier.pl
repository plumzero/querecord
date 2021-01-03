
#!/usr/bin/env perl -w


### star * 测试 ###

my $str = "fredbarney";
if ($str =~ /fred\t*barney/) {
    print "star: 0 tab matched!\n";
} else {
    print "star: 0 tab not matched!\n";
}

$str = "fred\tbarney";
if ($str =~ /fred\t*barney/) {
    print "star: 1 tab matched!\n";
} else {
    print "star: 1 tab not matched!\n";
}

$str = "fred\t\t\tbarney";
if ($str =~ /fred\t*barney/) {
    print "star: 3 tabs matched!\n";
} else {
    print "star: 3 tabs not matched!\n";
}

$str = "fred\t\\\tbarney";
if ($str =~ /fred\t*barney/) {
    print "star: exception occured!\n";
} else {
    print "star: not matched!\n";
}


### plus + 测试 ###

print "\n";

$str = "fredbarney";
if ($str =~ /fred\t+barney/) {
    print "plus: 0 tab matched!\n";
} else {
    print "plus: 0 tab not matched!\n";
}

$str = "fred\tbarney";
if ($str =~ /fred\t+barney/) {
    print "plus: 1 tab matched!\n";
} else {
    print "plus: 1 tab not matched!\n";
}

$str = "fred\t\t\tbarney";
if ($str =~ /fred\t+barney/) {
    print "plus: 3 tabs matched!\n";
} else {
    print "plus: 3 tabs not matched!\n";
}


### ques ? 测试 ###

print "\n";

$str = "/bammbamm/";
if ($str =~ /bamm-?bamm/) {
    print "ques: 0 matched!\n";
} else {
    print "ques: 0 not matched!\n";
}

$str = "/bamm-bamm/";
if ($str =~ /bamm-?bamm/) {
    print "ques: 1 matched!\n";
} else {
    print "ques: 1 not matched!\n";
}

$str = "/bamm--bamm/";
if ($str =~ /bamm-?bamm/) {
    print "ques: 2 matched!\n";
} else {
    print "ques: 2 not matched!\n";
}
