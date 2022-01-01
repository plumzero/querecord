
'use strict';

const { Server } = require('http');
const { MongoClient } = require('mongodb');
// or as an es module:
// import { MongoClient } from 'mongodb'

// Connection URL
const url = 'mongodb://tester:helloworld@localhost:27017';
const client = new MongoClient(url, { authSource: 'admin' });

// Database Name
const dbName = 'online';

async function main() {
    // Use connect method to connect to the server
    await client.connect();
    console.log('Connected successfully to server');
    const db = client.db(dbName);
    const collection = db.collection('minute_mkdata_20211228');

    // the following code examples can be pasted here...
    const findResult = await collection.find({},{'symbol':1, 'nTime':1}).toArray();
    console.log('Found documents =>', findResult);

    return 'done.';
}

main()
    .then(console.log)
    .catch(console.error)
    .finally(() => client.close());
