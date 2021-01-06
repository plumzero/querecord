
#!/usr/bin/env perl -w

use strict;

BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::PP'; }
use JSON;

my %rec_hash = (
                'a' => 1,
                'b' => 2,
                'c' => 3,
                'd' => 4,
                'e' => 5
               );

my $json = to_json(\%rec_hash);

printf("%s\n", $json);


## format print 
my $json_fmt = to_json(\%rec_hash, {utf8 => 1, pretty => 1 });

printf("%s\n", $json_fmt);
