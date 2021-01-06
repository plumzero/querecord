
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

my $json = encode_json(\%rec_hash);

my $json_text = JSON->new->utf8->encode(\%rec_hash);

printf("%s\n", $json);

printf("%s\n", $json_text);