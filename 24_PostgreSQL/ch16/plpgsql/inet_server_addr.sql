
-- 该脚本必须指定 -h ip地址 执行才能达到预期效果。如:
--   psql -h 192.168.a.b -p 5432 testdb pguser
--   
--   因为 inet_server_addr 有 bug ，如下:
--     In PostgreSQL 13 and earlier, inet_server_addr() will always return NULL if executed by a parallel worker. 
--     This has been fixed for PostgreSQL 14 (commit 5a6f9bce), but has not been backpatched to earlier versions. 

DO
$haha$
DECLARE
    _server_ip text;
BEGIN
    SELECT host(inet_server_addr())::text INTO _server_ip;
    IF _server_ip = '192.168.2.104' THEN
        RAISE INFO '测试环境';
    ELSIF _server_ip = '192.168.2.200' THEN
        RAISE INFO '正式环境';
    ELSIF _server_ip = '192.168.2.102' THEN
        RAISE INFO '开发环境';
    ELSE
        RAISE INFO '未知环境 %', _server_ip;
    END IF;
END;
$haha$
LANGUAGE plpgsql;
