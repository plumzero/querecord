#!/usr/bin/env perl -w

use strict;
use Socket;

my $port = shift || 7890;
my $proto = getprotobyname('tcp');
my $server = "localhost";


socket(SOCKET, AF_INET, SOCK_STREAM, $proto) or die("created socket failed: $!\n");

setsockopt(SOCKET, SOL_SOCKET, SO_REUSEADDR, 1) or die("set SO_REUSEADDR failed: $!\n");

bind(SOCKET, pack_sockaddr_in($port, inet_aton($server))) or die("bind to $port failed: $!\n");

listen(SOCKET, 5) or die("listen failed: $!\n");

print("start at port: $port\n");


my $client_addr;

while($client_addr = accept(NEW_SOCKET, SOCKET))
{
    my $name = gethostbyaddr($client_addr, AF_INET) or warn("get host failed\n");
    
    print("Connection recieved from $name\n");
    
    print(NEW_SOCKET  "this message created by Server will send to Client");
    
    close NEW_SOCKET;
}
