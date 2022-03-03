
import mongodb from 'mongodb';
import util from 'util';
import fs from 'fs';
import path from 'path';
import readline from 'readline';
import moment from 'moment';
import os from 'os';

// npm init -y
// npm install --save mongodb@3.6.2
// npm install moment --save
// package.json     "type": "module",

const __dirname = path.resolve();

let _client = null;

let _mongo_addr = '192.168.2.104:37017';
let _mongo_user = 'yourname';
let _mongo_password = 'yourpassword';

async function mgoCli() {
    if (! _client) {
        const url = util.format("mongodb://%s:%s@%s", _mongo_user, _mongo_password, _mongo_addr);
        _client = await mongodb.connect(url, {useUnifiedTopology: true});
        console.log('connect to mongodb success');
    }

    return _client;
}

function getLocalIP() {
    const osType = os.type();
    const netInfo = os.networkInterfaces();

    return netInfo.eth0[0].address;
}

async function main() {
    let _date = moment().format('YYYYMMDD');

    let _path_read = '';

    // 读取帐户文件
    const readStream = fs.createReadStream(_path_read);
    const rl = readline.createInterface({
        input: readStream,
        crlfDelay: Infinity
    });
    const dics = {};
    for await (const line of rl) {
        let kvs = line.split(',');
        let id, name;
        kvs.forEach((item, index, array) => {
            let kv = item.split(':');
            if (kv[0] === 'id') {
                id = kv[1];
            } else if (kv[0] === 'name') {
                name = kv[1];
            }
        });
        dics[id] = name;
    }
    rl.close();
    for (let k in dics) {
        console.log(k, " => ", dics[k]);
    }
    // 打开写文件
    let filename = path.resolve(__dirname, './write.txt');
    const writeStream = fs.createWriteStream(filename);
    writeStream.on('error', (err) => {
        console.log('写入时异常', err);
    });
    writeStream.on('open', (fd) => {
        console.log('文件描述符打开', fd);
    });
    writeStream.on('finish', () => {
        console.log('写入完成');
    });
    writeStream.on('close', () => {
        console.log('关闭文件');
    });
    // 从 MongoDB读取订单文件
    let dbname = 'mydb';
    let collname = 'mycoll';
    const cli = await mgoCli();
    const db = await cli.db(dbname);
    const coll = await db.collection(collname);
    const orders = await coll.find().limit(3).toArray();
    orders.forEach((item, index, array) => {
        let _bigid = item.bigid.toString();
        let _pre = item.pre.toString();
        let _id = item.bigid.toString().substr(_pre.length, _bigid.length);
        let _str = item.str.padStart(9, '0');
        let _time = moment(item.time).format('HmmssSSS');
        let _name = '';
        let _account = item.account.toString();
        if (_account in dics) {
            _name = dics[_account];
        }
        let fmt_string = `id:${_id},str:${_str},time:${_time},name:${_name}`
                       + `\n`;
        writeStream.write(fmt_string);
    });
    writeStream.end();
}

main();
