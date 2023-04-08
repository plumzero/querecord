
#!/usr/bin/env perl -w

{
  my @bootlogs = glob '/var/log/boot*';

  foreach (@bootlogs) {
    print "$_\n";
  }
}

{
  foreach (glob '/var/log/boot*') {
    print "$_\n";
  }
}

