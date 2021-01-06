
#!/usr/bin/env perl -w

use strict;

BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::PP'; }
use JSON;
use Data::Dumper;

my $json = '{"a":1,"b":2,"c":3,"d":4,"e":5}';

my $text = from_json($json);

print Dumper($text);
