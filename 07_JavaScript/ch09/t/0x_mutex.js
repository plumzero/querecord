
import { Mutex } from './mutex.js';

// 测试

let sleep = async(delay) => {
    return new Promise((resolve) => setTimeout(resolve, delay));
};

let clock = () => {
    return new Date().toTimeString();
};

let mtx = new Mutex();

let thread_1 = async() => {
    console.log('%s: thread-1 begin its work', clock());
    await mtx.lock();
    console.log('%s: thread-1 would work 5 seconds', clock());
    await sleep(5000);
    mtx.unlock();
    console.log('%s: thread-1 end its work', clock());
};

let thread_2 = async() => {
    await sleep(1000);
    console.log('%s: thread-1 begin its work', clock());
    await mtx.lock();
    console.log('%s: thread-2 would work for 2 seconds', clock());
    await sleep(2000);
    mtx.unlock();
    console.log('%s: thread-2 end its work', clock());
};

async function main() {
    thread_1();
    thread_2();
}

main().then(res => console.log('res:', res)).catch(err => console.log('err:', err));

setInterval(() => {}, 1000);
