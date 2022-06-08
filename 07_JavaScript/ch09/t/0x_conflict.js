
import { Mutex } from './mutex.js';

let mtx = new Mutex();

let total = 1000000000;
let incr = 0;

let dic = {
    thread_1: 0,
    thread_2: 0,
    thread_3: 0
};

let sleep = async(delay) => {
    return new Promise((resolve) => setTimeout(resolve, delay));
};

let thread_1 = async() => {
    console.log('thread-1');
    while (incr < total) {
        if (incr < 1000) {
            await sleep(1);   
        }
        await mtx.lock();
        ++incr;
        mtx.unlock();
        dic.thread_1++;
    }
};

let thread_2 = async() => {
    console.log('thread-2');
    while (incr < total) {
        if (incr < 1000) {
            await sleep(1);   
        }
        await mtx.lock();
        ++incr;
        mtx.unlock();
        dic.thread_2++;
    }
};

let thread_3 = async() => {
    console.log('thread-3');
    while (incr < total) {
        if (incr < 1000) {
            await sleep(1);   
        }
        await mtx.lock();
        ++incr;
        mtx.unlock();
        dic.thread_3++;
    }
};

let funcs = [ thread_1, thread_2, thread_3 ];

async function main() {
    for (let func of funcs) {
        func();
    }
}

main().then().catch(err => console.log('err:', err));

setTimeout(() => {
    console.log('incr: %d', incr);
    console.log('thread_1(%d) + thread_2(%d) + thread_3(%d) = %d', dic.thread_1, dic.thread_2, dic.thread_3, dic.thread_1 + dic.thread_2 + dic.thread_3);
    process.exit(0);
}, 10000);
