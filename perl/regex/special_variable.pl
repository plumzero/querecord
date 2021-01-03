
#!/usr/bin/env perl -w

$str = "yabba dabba doo";

if (/abba/) {
    print "It matched!\n";
} else {
    print "Not matched!\n";
}


$str = "yabba dabba doo";

if ($str =~ /abba/) {
    print "It matched!\n";
} else {
    print "Not matched!\n";
}


$_ = "yabba dabba doo";

if (/abba/) {
    print "It matched!\n";
} else {
    print "Not matched!\n";
}

