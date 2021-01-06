
#!/usr/bin/env perl -w

use strict;

BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::PP'; }
use JSON;
use Encode;

my %rec_hash = (
                'a' => 1,
                'b' => 2,
                'c' => 3,
                'd' => 4,
                'e' => 5
               );

my $json = JSON->new();

my $jsontext = encode("UTF-8", $json->encode(\%rec_hash));

print "$jsontext\n";
