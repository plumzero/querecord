
#!/usr/bin/env perl -w

use strict;

BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::PP'; }
use JSON;
use Encode;

my $json = JSON->new();

{
    my %settings = %{$json->property()};

    foreach my $key (keys %settings) {
        print "key=$key, value=$settings{$key}\n";
    }
}

{
    my $enabled = $json->get_indent();
    print "indent enabled=$enabled\n";

    my $enable = 0;
    $json = $json->indent($enable);

    $enabled = $json->get_indent();

    print "indent enabled=$enabled\n";
}
