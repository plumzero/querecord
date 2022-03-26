
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

    var i;
    for (i = 0; i < 100; i++) {
        let v = {
            id: i,
            str: "str_" + i,
        }
        await coll.insertOne(v);
    }

    let array = [];
    for (; i < 110; i++) {
        let v = {
            id: i,
            str: "str_" + i,
        }
        array.push(v);
    }
    await coll.insertMany(array);

    let len = await coll.find().count();
    console.log("len: %d", len);

    await mgocli.close();
}

main()
    .then(() => {})
    .catch(err => console.error(err));
