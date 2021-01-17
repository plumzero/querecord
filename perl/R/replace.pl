
#!/usr/bin/env perl -w

{
    $_ = "He's out bowling with Barney tonight.";
    s/Barney/Fred/;
    print "$_\n";
}

{
    $_ = "He's out bowling with Barney tonight.";
    s/with (\w+)/against $1's team/;
    print "$_\n";
}


#
# global
#

{
    $_ = "home, sweet home!";
    s/home/cave/g;
    print "$_\n";
}

{
    $_ = "Input  data\t may have    extra whitespace.";
    s/\s+/ /g;
    print "$_\n";
}


#
# Convert to upper or lower
#
{
    $_ = "I saw Barney with Fred.";
    s/(fred|barney)/\U$1/gi;
    print "$_\n";
}

{
    $_ = "I saw Barney with Fred.";
    s/(fred|barney)/\L$1/gi;
    print "$_\n";
}

{
    $_ = "I saw Barney with Fred.";
    s/(\w+) with (\w+)/\U$2 with $1/i;
    print "$_\n";
}

{
    $_ = "I saw Barney with Fred.";
    s/(\w+) with (\w+)/\U$2\E with $1/i;
    print "$_\n";
}

{
    $_ = "I saw Barney with Fred.";
    s/(\w+) with (\w+)/\u$2 with $1/i;
    print "$_\n";
}