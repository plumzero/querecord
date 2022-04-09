
import Redis from './redis.js';

let config = {
    host: '192.168.2.102',
    port: 6379,
    password: 'xxx',
    detect_buffers: true,
    retry_strategy: function(options) {
        if (options.error && options.error.code === "ECONNREFUSED") {
          // End reconnecting on a specific error and flush all commands with
          // a individual error
          return new Error("The server refused the connection");
        }
        if (options.total_retry_time > 1000 * 60 * 60) {
          // End reconnecting after a specific timeout and flush all commands
          // with a individual error
          return new Error("Retry time exhausted");
        }
        if (options.attempt > 10) {
          // End reconnecting with built in error
          return undefined;
        }
        // reconnect after
        return Math.min(options.attempt * 100, 3000);
    }
};

async function test_set_get() {
    let rc = new Redis(config);

    console.log('str exists? :', await rc.exists('str'));
    console.log('str set? :', await rc.set('str', 'Hello World'));
    console.log('str exists? :', await rc.exists('str'));
    console.log('str get? :', await rc.get('str'));
    console.log('str del? :', await rc.del('str'));
    console.log('str exists? :', await rc.exists('str'));

    console.log('num exists? :', await rc.exists('num'));
    console.log('num set? :', await rc.set('num', 123));
    console.log('num exists? :', await rc.exists('num'));
    console.log('num get? :', await rc.get('num'));
    console.log('num del? :', await rc.del('num'));
    console.log('str exists? :', await rc.exists('str'));

    rc.close();

    return '==== set/get ok ====';
}

async function test_hset_hget() {
    let rc = new Redis(config);

    console.log('ht exists? :', await rc.hexists('ht', 'key1'));
    console.log('ht hset? :', await rc.hset('ht', 'key1', 'val1'));
    console.log('ht exists? :', await rc.hexists('ht', 'key1'));
    console.log('ht hget? :', await rc.hget('ht', 'key1'));
    console.log('ht hdel? :', await rc.hdel('ht', 'key1'));
    console.log('ht exists? :', await rc.hexists('ht', 'key1'));

    console.log('arr exists? :', await rc.exists('arr'));
    console.log('arr hmset', await rc.hmset('arr', [ 10, 20, 30 ]));
    console.log('arr exists? :', await rc.exists('arr'));
    console.log('arr hget? :', await rc.hget('arr', '1'));
    console.log('arr del? :', await rc.del('arr'));
    console.log('arr exists? :', await rc.exists('arr'));

    console.log('colors exists? :', await rc.exists('colors'));
    console.log('colors hmset', await rc.hmset('colors', [ 'red', 'green', 'blue' ]));
    console.log('colors exists? :', await rc.exists('colors'));
    console.log('colors hget? :', await rc.hget('colors', '2'));
    console.log('colors del? :', await rc.del('colors'));
    console.log('colors exists? :', await rc.exists('colors'));

    console.log('obj exists? :', await rc.exists('obj'));
    console.log('obj hmset', await rc.hmset('obj', { 'name': 'zhangsan', 'age': 30 }));
    console.log('obj exists? :', await rc.exists('obj'));
    console.log('obj hget? :', await rc.hget('obj', 'name'));
    console.log('obj hget? :', await rc.hget('obj', 'age'));
    console.log('obj del? :', await rc.del('obj'));
    console.log('obj exists? :', await rc.exists('obj'));

    // 数组长度为 0 的情况
    console.log('arr exists? :', await rc.exists('arr'));
    console.log('arr hmset', await rc.hmset('arr', [ 10, 20, 30 ]));
    console.log('arr exists? :', await rc.exists('arr'));
    console.log('arr hget? :', await rc.hget('arr', '1'));
    console.log('arr hmset', await rc.hmset('arr', [ ]));
    console.log('arr exists? :', await rc.exists('arr'));

    // 对象为空的情况
    console.log('obj exists? :', await rc.exists('obj'));
    console.log('obj hmset', await rc.hmset('obj', { 'name': 'zhangsan', 'age': 30 }));
    console.log('obj exists? :', await rc.exists('obj'));
    console.log('obj hget? :', await rc.hget('obj', 'name'));
    console.log('obj hget? :', await rc.hget('obj', 'age'));
    console.log('obj hmset', await rc.hmset('obj', {}));
    console.log('obj exists? :', await rc.exists('obj'));

    rc.close();

    return '==== hset/hget ok ====';
}

async function test_list() {
    let rc = new Redis(config);

    console.log('lst exists? :', await rc.exists('lst'));
    console.log('lst rpush? :', await rc.rpush('lst', 1));
    console.log('lst rpush? :', await rc.rpush('lst', 2));
    console.log('lst llen? :', await rc.llen('lst'));
    console.log('lst rpush? :', await rc.rpush('lst', [ 4, 8, 16]));
    console.log('lst llen? :', await rc.llen('lst'));
    console.log('lst lindex? :', await rc.lindex('lst', 3));
    console.log('lst lrange? ：', await rc.lrange('lst', 0, -1));
    console.log('lst lrem? :', await rc.lrem('lst', -2, 4));
    console.log('lst llen? :', await rc.llen('lst'));
    console.log('lst lrange? ：', await rc.lrange('lst', 0, -1));
    console.log('lst del? :', await rc.del('lst'));
    console.log('lst exists? :', await rc.exists('lst'));

    console.log('colors exists? :', await rc.exists('colors'));
    console.log('colors rpush? :', await rc.rpush('colors', 'red'));
    console.log('colors rpush? :', await rc.rpush('colors', 'green'));
    console.log('colors rpush? :', await rc.rpush('colors', [ 'red', 'blue', 'red', 'red', 'green']));
    console.log('colors llen? :', await rc.llen('colors'));
    console.log('colors lindex? :', await rc.lindex('colors', 3));
    console.log('colors lrange? ：', await rc.lrange('colors', 0, -1));
    console.log('colors lrem? :', await rc.lrem('colors', -2, 'red'));
    console.log('colors llen? :', await rc.llen('colors'));
    console.log('colors lrange? ：', await rc.lrange('colors', 0, -1));
    console.log('colors del? :', await rc.del('colors'));
    console.log('colors exists? :', await rc.exists('colors'));

    rc.close();

    return '==== list ok ====';
}

// test_set_get()
//     .then((res) => console.log(res))
//     .catch((err) => console.log(err));

// test_hset_hget()
//     .then((res) => console.log(res))
//     .catch((err) => console.log(err));

test_list()
    .then((res) => console.log(res))
    .catch((err) => console.log(err));