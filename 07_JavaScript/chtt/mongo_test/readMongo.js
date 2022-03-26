
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
    let coll_name = 'mycoll';
    let mgocli = await mgoCli();
    let db = await mgocli.db(dbname);
    let coll = await db.collection(coll_name);
    let len = await coll.find().count();

    console.log("len=%d", len);
    let skips = 12;
    let array = [];
    for (let i = 0; i < len; i += skips) {
        let s = await coll.find().skip(i).limit(skips).toArray();
        array.push(...s);
    }
    console.log("array.length=%d", array.length);

    await mgocli.close();
}

main()
    .then(() => {})
    .catch(err => console.error(err));
