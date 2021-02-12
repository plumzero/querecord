
#!/usr/bin/env perl -w

use DBI;
use strict;

my $host = "127.0.0.1";
my $port = 5432;
my $driver = "Pg";
my $database = "testdb";

# 驱动程序对象的句柄
my $dsn = "DBI:$driver:database=$database;host=$host;port=$port";
my $userid = "postgres";
my $password = "1234";

# 连接数据库
my $dbh = DBI->connect($dsn, $userid, $password) or die $DBI::errstr;

print "Opened database successfully\n";

$dbh->disconnect();
