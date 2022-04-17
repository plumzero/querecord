
import MongoClient from './mongo.js';

let _mongo_user = 'test';
let _mongo_password = 'test123';

let _host = '192.168.2.102:27017';
let _mgc = null;

async function mgoCli() {
    if (! _mgc) {
        _mgc = await MongoClient({ user: _mongo_user, password: _mongo_password, host: _host });
    }

    return _mgc;
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