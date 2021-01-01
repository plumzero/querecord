
#!/usr/bin/env perl -w

$bar = "I am runoob site. welcome to runoob site.";
if ($bar =~ /run/){
    print "匹配前的字符串: $`\n";
    print "匹配到的字符串: $&\n";
    print "匹配后的字符串: $'\n";
}else{
    print("第一次不匹配\n");
}
