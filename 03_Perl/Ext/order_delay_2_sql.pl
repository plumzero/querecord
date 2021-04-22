
#!/usr/bin/env perl -w

# *******************************************
# Script Status: 完结 
# Creation Data:
# Last Modified:
# Author:
# E-mail:
# *******************************************
# Description: 将每个对象各状态的延迟(json格式)发送到数据库
# *******************************************
# Usage:
#   perl order_delay_2_sql.pl
#   perl order_delay_2_sql.pl 20210108
# *******************************************

use strict;
use DBI;
use JSON;

### connect to db
my $host = "127.0.0.1";
my $port = 5432;
my $driver = "Pg";
my $database = "testdb";
my $dsn = "DBI:$driver:database=$database;host=$host;port=$port";
my $userid = "postgres";
my $password = "1234";

my $dbh = DBI->connect($dsn, $userid, $password) or die $DBI::errstr;

print "opened database successfully\n";

# read file
my $filename = "order_delay_" . strftime("%Y_%m_%d", localtime) . ".txt";

open(DATA, "<$filename") or die "open $filename failed: $!\n";

my $xsjson = <DATA>;

my %stdata = %{JSON->new->utf8()->convert_blessed(1)->allow_nonref(1)->decode($xsjson)};

### insert into

foreach my $key (keys %stdata)
{
    my $_reqid = $key;
    my $_none = 0;
    my $_none_pending = 0;
    my $_pending_accepted = 0;
    my $_pending_totalremoved = 0;
    my $_pending_failed = 0;
    my $_accepted_totalmatch = 0;
    my $_accepted_partialremoved = 0;
    my $_end_state = "";

    my %order = %{$stdata{$key}};
    
    foreach my $k (keys %order)
    {
        if ($k eq "None") {
            $_none = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "None_Pending") {
            $_none_pending = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "Pending_Accepted") {
            $_pending_accepted = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "Pending_TotalRemoved") {
            $_pending_totalremoved = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "Pending_Failed") {
            $_pending_failed = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "Accepted_TotalMatch") {
            $_accepted_totalmatch = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "Accepted_PartialRemoved") {
            $_accepted_partialremoved = $order{$k} ? $order{$k} : 0;
        } elsif ($k eq "end_state") {
            $_end_state = $order{$k};
        }
    }
    
    printf("reqid=%d,end_state=%s,none=%d,none_pending=%d,pending_accepted=%d,pending_totalremoved=%d,pending_failed=%d,accepted_totalmatch=%d,accepted_partialremoved=%d\n",
            $_reqid, $_end_state, $_none, $_none_pending, $_pending_accepted, $_pending_totalremoved, $_pending_failed, $_accepted_totalmatch, $_accepted_partialremoved);
    
    my $stmt = qq(insert into order_delay(reqid, end_state, none, none_pending, pending_accepted, pending_totalremoved, pending_failed, accepted_totalmatch, accepted_partialremoved)
                  values ($_reqid, '$_end_state', $_none, $_none_pending, $_pending_accepted, $_pending_totalremoved, $_pending_failed, $_accepted_totalmatch, $_accepted_partialremoved));
    
    my $rv = $dbh->do($stmt) or die $dbi::errstr;
    
    print "records inserted successfully\n";
}

$dbh->disconnect();
