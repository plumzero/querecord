
import events from 'events';

async function sleep(delay) {
    return new Promise((resolve) => setTimeout(resolve, delay));
}

// 适时地添加和删除事件
let ee = new events.EventEmitter().setMaxListeners(0);

let handler = () => { console.log('%s: 新事件触发', new Date().toTimeString()); };

ee.on('add-remove', (arg) => {
    if (Number(arg) == 2) {
        ee.addListener('bar', handler);
        console.log('%s: 添加事件', new Date().toTimeString());
    } else if (Number(arg) == 4) {
        ee.removeListener('bar', handler);
        console.log('%s: 删除事件', new Date().toTimeString());
    } else {
        console.log('%s: 不做动作', new Date().toTimeString());
    }
});

async function test() {
    console.log("%s: 开始测试", new Date().toTimeString());

    for (let i = 0; i < 7; i++) {
        ee.emit('add-remove', i);
        ee.emit('bar');
        await sleep(2000);
    }

    console.log("%s: 结束测试", new Date().toTimeString());
}

test();
