#!/usr/bin/env perl -w

use strict;
use warnings;

use Socket;


my $host = shift || 'localhost';
my $port = shift || 7890;
my $server = "localhost";


socket(SOCKET, AF_INET, SOCK_STREAM, (getprotobyname('tcp'))[2]) or die("created socket failed: $!\n");

connect(SOCKET, pack_sockaddr_in($port, inet_aton($server))) or die("connected port $port failed $!\n");

my $line;

while ($line = <SOCKET>)
{
    print("$line\n");
}

close(SOCKET) or die("close failed: $!\n");
