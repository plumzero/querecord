
#!/usr/bin/env perl -w

if ("Hello there, neighbor" =~ /\s(\w+),/) {
    print "That actually matched '$&'.\n";
}

if ("Hello there, neighbor" =~ /\s(\w+),/) {
    print "That actually matched '$1'.\n";
}

if ("Hello there, neighbor" =~ /\s(\w+),/) {
    print "That was ($`)($&)($').\n";
}

