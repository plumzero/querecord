
import { RWMutex } from './mutex.js';

// 测试

let sleep = async(delay) => {
    return new Promise((resolve) => setTimeout(resolve, delay));
};

let clock = () => {
    return new Date().toTimeString();
};

let mtx = new RWMutex();

let thread_read_1 = async() => {
    let name = 'read-1';
    console.log('%s: thread_read_1 wait for its work', clock());
    await mtx.rLock(name);
    console.log('%s: thread_read_1 begin and would work for 5 seconds', clock());
    await sleep(5000);
    mtx.rUnlock(name);
    console.log('%s: thread_read_1 end its work', clock());
};

let thread_read_2 = async() => {
    let name = 'read-2';
    await sleep(1000);
    console.log('%s: thread_read_2 wait for its work', clock());
    await mtx.rLock(name);
    console.log('%s: thread_read_2 begin and would work for 2 seconds', clock());
    await sleep(2000);
    mtx.rUnlock(name);
    console.log('%s: thread_read_2 end its work', clock());
};

let thread_read_3 = async() => {
    let name = 'read-3';
    await sleep(3000);
    console.log('%s: thread_read_3 wait for its work', clock());
    await mtx.rLock(name);
    console.log('%s: thread_read_3 begin and would work for 2 seconds', clock());
    await sleep(2000);
    mtx.rUnlock(name);
    console.log('%s: thread_read_3 end its work', clock());
};

let thread_read_4 = async() => {
    let name = 'read-4';
    await sleep(4000);
    console.log('%s: thread_read_4 wait for its work', clock());
    await mtx.rLock(name);
    console.log('%s: thread_read_4 begin and would work for 4 seconds', clock());
    await sleep(4000);
    mtx.rUnlock(name);
    console.log('%s: thread_read_4 end its work', clock());
};

let thread_write = async() => {
    await sleep(2000);
    console.log('%s: thread_write wait for its work', clock());
    await mtx.wLock();
    console.log('%s: thread_write begin and would work for 8 seconds', clock());
    await sleep(8000);
    mtx.wUnlock();
    console.log('%s: thread_write end its work', clock());
};

async function main() {
    thread_read_1();
    thread_read_2();
    thread_read_3();
    thread_write();
    thread_read_4();
}

main().then(res => console.log('res:', res)).catch(err => console.log('err:', err));

setInterval(() => {}, 1000);
