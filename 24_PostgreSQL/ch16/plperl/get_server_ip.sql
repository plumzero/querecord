-- 由于 get_server_ip() 函数中使用了 shell，所以必须以 postgres 用户执行

-- 想要从 get_server_ip() 中返回字符串，暂时还不能呀

CREATE OR REPLACE FUNCTION get_server_ip()
RETURNS void AS
$$
    use strict;
    use warnings;

    my $server_ip;
    foreach (`ip -o -4 address`) {
        my($this_ip) = /inet\s+(.+)\//;
        if ($this_ip =~ /192\.168/) {
            $server_ip = $this_ip;
        }
    }
    elog(INFO, "server_ip = $server_ip");
$$
LANGUAGE plperlu;

-- 流程
DO
$haha$
DECLARE

BEGIN
    PERFORM get_server_ip();
END;
$haha$
LANGUAGE plpgsql;

DROP FUNCTION IF EXISTS get_server_ip();
