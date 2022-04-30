
import events from 'events';

async function sleep(delay) {
    return new Promise((resolve) => setTimeout(resolve, delay));
}

let ee = new events.EventEmitter().setMaxListeners(0);

// 只触发第一次
ee.once('event-once-noargs', () => {
    console.log('%s', new Date().toTimeString());
});

ee.once('event-once-args', (args) => {
    console.log('%s: ', new Date().toTimeString(), args);
});

async function test() {
    console.log("%s: 开始测试", new Date().toTimeString());

    for (let i = 0; i < 5; i++) {
        ee.emit('event-once-noargs');
        ee.emit('event-once-args', i * 100);
        await sleep(2000);
    }

    console.log("%s: 结束测试", new Date().toTimeString());
}

test();
