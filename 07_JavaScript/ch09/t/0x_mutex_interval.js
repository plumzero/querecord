
import { Mutex } from './mutex.js';

let mtx = new Mutex();

let total = 10000;
let incr = 0;

let interval = 1;

let array = [];
let dic = {
    thread_1: 0,
    thread_2: 0,
    thread_3: 0
};

let thread_1 = async() => {
    setInterval(async() => {
        await mtx.lock();
        if (incr < total) {
            array.push(++incr);
            dic.thread_1++;
        }
        mtx.unlock();
    }, interval);
};

let thread_2 = async() => {
    setInterval(async() => {
        await mtx.lock();
        if (incr < total) {
            array.push(++incr);
            dic.thread_2++;
        }
        mtx.unlock();
    }, interval);
};

let thread_3 = async() => {
    setInterval(async() => {
        await mtx.lock();
        if (incr < total) {
            array.push(++incr);
            dic.thread_3++;
        }
        mtx.unlock();
    }, interval);
};

let funcs = [ thread_1, thread_2, thread_3 ];

async function main() {
    for (let func of funcs) {
        func();
    }
}

main().then().catch(err => console.log('err:', err));

setTimeout(() => {
    console.log('array.length: %d, incr: %d', array.length, incr);
    console.log('thread_1(%d) + thread_2(%d) + thread_3(%d) = %d', dic.thread_1, dic.thread_2, dic.thread_3, dic.thread_1 + dic.thread_2 + dic.thread_3);
    process.exit(0);    
}, 10000);
