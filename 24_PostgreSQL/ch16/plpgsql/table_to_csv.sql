
-- 表数据转为指定格式数据

\o /dev/null

DO
$Tiaramisu$
DECLARE
    obj RECORD;
    result text;

    _reqid text;
    _symbol text;
    _accountid text;
    _type text;
    _status text;
    _ordvol text;
    _dealvol text;
    _subtime text;
    _closetime text;
    _server text;
    _orderprice text;
    _dealprice text;
    _trader text;
    _tag text;
    _orderId text;
    _nTime text;
    _timeout text;
    _force text;
    _createTime text;
    _acceptTime text;
    _errCode text;
    _group text;
    _dri text;
    _dio text;
    _dia text;
    _dam text;
BEGIN
    FOR obj IN SELECT * FROM tbl_trade_order LIMIT 1
    LOOP
        
        RAISE INFO '--> %', obj;
        -- id serverId
        SELECT ltrim(obj."id"::text, obj."serverId"::text) INTO _reqid;
        -- symbol
        SELECT obj."symbol" INTO _symbol;
        IF _symbol::INTEGER > 600000 THEN
            SELECT format('%s.SH', _symbol) INTO _symbol;
        ELSE
            SELECT format('%s.SZ', _symbol) INTO _symbol;
        END IF;
        -- account
        SELECT obj."account" INTO _accountid;
        -- type
        SELECT obj."type" INTO _type;
        -- status
        SELECT
            CASE WHEN obj."status" = 1 THEN '正报'
                 WHEN obj."status" = 2 THEN '已报'
                 WHEN obj."status" = 3 THEN '部成'
                 WHEN obj."status" = 4 THEN '已成'
                 WHEN obj."status" = 5 THEN '部撤'
                 WHEN obj."status" = 6 THEN '已撤'
                 WHEN obj."status" = 7 THEN '废单'
                 WHEN obj."status" = 8 THEN '正撤'
                 ELSE '未定'
            END
        INTO _status;
        -- orderVolumn
        SELECT obj."orderVolumn" INTO _ordvol;
        -- dealVolumn
        SELECT obj."dealVolumn" INTO _dealvol;
        -- submitTime
        SELECT to_char(to_timestamp(obj."submitTime"::DOUBLE PRECISION / 1000), 'HH24MISSMS') INTO _subtime;
        -- closeTime
        SELECT to_char(to_timestamp(obj."closeTime"::DOUBLE PRECISION / 1000), 'HH24MISSMS') INTO _closetime;
        -- serverId
        SELECT obj."serverId" INTO _server;
        -- orderPrice
        SELECT obj."orderPrice" INTO _orderprice;
        -- dealPrice
        SELECT obj."dealPrice" INTO _dealprice;
        -- tag  将 tag 赋值给 trader
        SELECT obj."tag" INTO _trader;
        -- risker 将 risker 以 '_' 分隔，将后半部分赋值给 tag
        SELECT split_part(obj."risker", '_', 2) INTO _tag;
        -- orderId
        SELECT obj."orderId" INTO _orderId;
        -- nTime
        SELECT obj."nTime" INTO _nTime;
        -- timeout
        SELECT obj."timeout" INTO _timeout;
        -- force
        SELECT obj."force"::boolean::text INTO _force;
        -- createTime
        SELECT to_char(to_timestamp(obj."closeTime"::DOUBLE PRECISION / 1000), 'HH24MISSMS') INTO _closetime;
        -- acceptTime
        SELECT to_char(to_timestamp(obj."acceptTime"::DOUBLE PRECISION / 1000), 'HH24MISSMS') INTO _acceptTime;
        -- errCode
        SELECT obj."errCode" INTO _errCode;
        -- tradedVolume
        -- 将此字段置为 0
        -- DRI
        SELECT obj."DRI" INTO _dri;
        -- DIO
        SELECT obj."DIO" INTO _dio;
        -- DIA
        SELECT obj."DIA" INTO _dia;
        -- DAM
        SELECT obj."DAM" INTO _dam;
    
        SELECT format('reqid:%s,symbol:%s,accountid:%s,type:%s,status:%s,ordvol:%s,dealvol:%s,subtime:%s,closetime:%s,'
                      'server:%s,orderprice:%s,dealprice:%s,trader:%s,tag:%s,orderId:%s,nTime:%s,timeout:%s,force:%s,'
                      'createTime:%s,acceptTime:%s,errCode:%s,tradedVolume:0,dri:%s,dio:%s,dia:%s,dam:%s',
                       _reqid, _symbol, _accountid, _type, _status, _ordvol, _dealvol, _subtime, _closetime,
                       _server, _orderprice, _dealprice, _trader, _tag, _orderId, _nTime, _timeout, _force,
                       _closetime, _acceptTime, _errCode, _dri, _dio, _dia, _dam)
        INTO result;
        RAISE INFO '%', result;
    END LOOP;
END;
$Tiaramisu$;

\o
