
#!/usr/bin/env perl -w

{
    foreach $rock (qw/ bedrock slate lava /) {
        print $rock . "\n";
    }
}

{
    my @nums = (10, 20, 30);

    foreach $ele (@nums) {
        $ele += 1;
    }

    foreach $ele (@nums) {
        print $ele . "\n";
    }
}

{
    foreach (qw/ bedrock slate lava /) {
        print $_ . "\n";
    }
}

{
    my @nums = (10, 20, 30);

    foreach (@nums) {
        $_ += 1;
    }

    foreach (@nums) {
        print $_ . "\n";
    }
}