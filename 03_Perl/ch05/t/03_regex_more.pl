
#!/usr/bin/env perl -w

{
    $_ = "I'm much better\n than Barney is\nat bowling, \nWilma.\n";
    if (/^wilma\b/im) {
        print "Found 'wilma' at start of line\n";
    }
}