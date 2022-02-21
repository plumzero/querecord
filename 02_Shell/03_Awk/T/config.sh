#!/usr/bin/env bash

set -euo pipefail

#
# config.sh -A 192.168.2.113:6543 -B airflow -K 192.168.2.113:6543 -L celery -X 192.168.2.113:6379 -Y 2
#

usage()
{
    echo "用法:"
    echo "  bash config.sh [-A 地址和端口] [-B 名称] [-C 角色] [-D 密码]"
    echo "                 [-K 地址和端口] [-L 名称] [-M 角色] [-N 密码]"
    echo "                 [-X 地址和端口] [-Y 名称] [-Z 密码]"
    echo "必填项说明:"
    echo "  -A    元数据地址和端口，如 192.168.2.113:6543"
    echo "  -B    元数据名称，必须是有效的数据库，如 testdb"
    echo "  -K    存储数据地址和端口，如 192.168.2.113:6543"
    echo "  -L    存储数据库名称，必须是有效的数据库，如 testdb"
    echo "  -X    redis数据库地址和端口，如 192.168.2.113:6379"
    echo "  -Y    redis数据库名称，选择 0~15 之间的任意库"
    echo "可选项说明:"
    echo "  -C   元数据库权限角色，默认使用 pguser"
    echo "  -D   元数据库认证密码，默认时根据其他脚本而定，需要改动"
    echo "  -M   存储数据库权限角色，默认使用 pguser"
    echo "  -N   存储数据库认证密码，默认时根据其他脚本而定，需要改动"
    echo "  -Z   redis数据库认证密码，默认使用..."
    echo "其他项说明:"
    echo "  -H,-h   帮助，打印此页"
    exit -1
}

if [[ $# -le 0 ]]; then
    usage
fi

METADB_IP=
METADB_NAME=
METADB_ROLE="pguser"
METADB_PWD=
DATADB_IP=
DATADB_NAME=
DATADB_ROLE="pguser"
DATADB_PWD=
REDIS_IP=
REDIS_DB=
REDIS_PWD="enterthis"

while getopts 'A:B:C:D:K:L:M:N:X:Y:ZHh' OPT
do
    case $OPT in
        A) METADB_IP="$OPTARG";;
        B) METADB_NAME="$OPTARG";;
        C) METADB_ROLE="$OPTARG";;
        D) METADB_PWD="$OPTARG";;
        K) DATADB_IP="$OPTARG";;
        L) DATADB_NAME="$OPTARG";;
        M) DATADB_ROLE="$OPTARG";;
        N) DATADB_PWD="$OPTARG";;
        X) REDIS_IP="$OPTARG";;
        Y) REDIS_DB="$OPTARG";;
        Z) REDIS_PWD="$OPTARG";;
        H) usage;;
        h) usage;;
        ?) usage;;
    esac
done

echo METADB_IP $METADB_IP
echo METADB_NAME $METADB_NAME
echo METADB_ROLE $METADB_ROLE
echo METADB_PWD $METADB_PWD
echo DATADB_IP $DATADB_IP
echo DATADB_NAME $DATADB_NAME
echo DATADB_ROLE $DATADB_ROLE
echo DATADB_PWD $DATADB_PWD

#
# 判空
#
[[ -z "$METADB_IP" ]]   && (echo "元数据地址和端口为空，退出"; exit -1)
[[ -z "$METADB_NAME" ]] && (echo "元数据名称为空，退出"; exit -1)
[[ -z "$DATADB_IP" ]]   && (echo "存储数据地址和端口为空，退出"; exit -1)
[[ -z "$DATADB_NAME" ]] && (echo "存储数据名称为空，退出"; exit -1)
[[ -z "$REDIS_IP" ]]    && (echo "redis数据地址和端口为空，退出"; exit -1)
[[ -z "$REDIS_DB" ]]    && (echo "redis数据名称为空，退出"; exit -1)

awk -v metadb_ip=$METADB_IP \
    -v metadb_name=$METADB_NAME \
    -v metadb_role=$METADB_ROLE \
    -v metadb_pwd=$METADB_PWD \
    -v datadb_ip=$DATADB_IP \
    -v datadb_name=$DATADB_NAME \
    -v datadb_role=$DATADB_ROLE \
    -v datadb_pwd=$DATADB_PWD \
    -v redis_ip=$REDIS_IP \
    -v redis_db=$REDIS_DB \
    -v redis_pwd=$REDIS_PWD \
    'BEGIN {
        # print metadb_ip;
        # print metadb_name;
        # print metadb_role;
        # print metadb_pwd;
        # print datadb_ip;
        # print datadb_name;
        # print datadb_role;
        # print datadb_pwd;
        # print redis_ip;
        # print redis_db;
        # print redis_pwd;
    }
    
    {
        if ($0 ~ /default_timezone = utc/) {
            gsub("utc", "system", $0);
            print $0;
        } else if (/executor = SequentialExecutor/) {
            gsub("SequentialExecutor", "CeleryExecutor", $0);
            print $0;
        } else if (/sql_alchemy_conn = sqlite/) {
            str = "sql_alchemy_conn = postgresql+psycopg2://" "" metadb_role "" ":" "" metadb_pwd "" "@" "" metadb_ip "" "/" "" metadb_name;
            gsub($0, str, $0);
            print $0;
        } else if (/load_examples = True/) {
            gsub("True", "False", $0);
            print $0;
        } else if (/load_default_connections = True/) {
            gsub("True", "False", $0);
            print $0;
        } else if (/auth_backend = airflow.api.auth.backend.deny_all/) {
            gsub("deny_all", "basic_auth", $0);
            print $0;
        } else if (/broker_url = redis/) {
            str = "broker_url = redis://:" "" redis_pwd "" "@" "" redis_ip "" "/" "" redis_db
            gsub($0, str, $0);
            print $0;
        } else if (/result_backend = db/) {
            str = "result_backend = db+postgresql+psycopg2://" "" datadb_role "" ":" "" datadb_pwd "" "@" "" datadb_ip "" "/" "" datadb_name;
            print str;
        } else {
            print $0;
        }
    }
    
    END {
    }' airflow.cfg.tmpl > airflow.cfg
