
#!/usr/bin/env perl -w

{
  my @fred = 6..10;
  
  my @barney = reverse(@fred);
  
  foreach (@fred) {
    print $_ . " ";
  }
  print "\n";
  
  foreach (@barney) {
    print $_ . " ";
  }
  print "\n";
}

{
  my @fred = 6..10;
  
  @fred = reverse(@fred);
  
  foreach (@fred) {
    print $_ . " ";
  }
  print "\n";
}