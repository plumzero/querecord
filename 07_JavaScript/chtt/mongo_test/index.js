
import mongodb from 'mongodb';
import util from 'util';

// npm init -y
// npm install --save mongodb@3.6.2

let _mongo_user = 'test';
let _mongo_password = 'test123';

let _host = '192.168.2.102:27017';
let _client = null;

async function mgoCli() {
    if (! _client) {
        const url = util.format("mongodb://%s:%s@%s", _mongo_user, _mongo_password, _host);
        _client = await mongodb.connect(url, {useUnifiedTopology: true});
        console.log('connect to mongodb(%s) success', _host);
    }

    return _client;
}

async function main() {
    let dbname = 'test';
    let coll_name = 'sales';
    let mgocli = await mgoCli();
    let db = await mgocli.db(dbname);
    let coll = await db.collection(coll_name);
    let indexes = await coll.indexes();

    // 创建索引的字段，其字段值必须是唯一的
    let v1 = {date: 1};
    let v2 = {};
    v2.background = true;
    v2.unique = true;
    await coll.createIndex(v1, v2);

    console.log("索引数量: %d", indexes.length);
    for (let i = 0; i < indexes.length; i++) {
        console.log("%s-%s: index[%d]=%j", dbname, coll_name, i, indexes[i]);
    }

    await mgocli.close();
}

main()
    .then(() => {})
    .catch(err => console.error(err));
