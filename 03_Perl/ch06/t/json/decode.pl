
#!/usr/bin/env perl -w

use strict;

BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::PP'; }
use JSON;

my $json = '{"a":1,"b":2,"c":3,"d":4,"e":5}';

my %text = %{decode_json($json)};

for my $key (sort keys %text) {
    printf("k=%s,v=%d\n", $key, $text{$key});
}
