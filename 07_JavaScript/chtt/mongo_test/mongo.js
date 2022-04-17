
import mongodb from 'mongodb';
import util from 'util';
import process from 'process';

async function MongoClient(conf) {
    if (conf.user === undefined) {
        console.log('must set a user(String) for mongo client explicitly');
        process.exit(-1);
    }
    if (conf.password === undefined) {
        console.log('must set a password(String) for mongo client explicitly');
        process.exit(-1);
    }
    if (conf.host === undefined) {
        console.log('must set a host(String) for mongo client explicitly');
        process.exit(-1);
    }

    let url = util.format("mongodb://%s:%s@%s", conf.user, conf.password, conf.host);

    return await mongodb.connect(url, {useUnifiedTopology: true});
}

export default MongoClient;
