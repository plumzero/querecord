
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
    let dbname = "test";
    let mgocli = await mgoCli();
    let db = await mgocli.db(dbname);
    let coll_list = await db.listCollections().toArray();
    console.log('数据库 %s 共 %d 个集合', dbname, coll_list.length);
    for await (const item of coll_list) {
        let coll_name = item.name;
        console.log("%s", coll_name);
    }

    await mgocli.close();
}

main()
    .then(() => {})
    .catch(err => console.error(err));
