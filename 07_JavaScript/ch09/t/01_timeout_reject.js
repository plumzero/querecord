
let p = new Promise((resolve, reject) => {
    setTimeout(reject, 10000);  // 10 秒后调用 reject()
    // 执行函数的逻辑
});

setTimeout(console.log, 0, p);  // Promise <pending>
setTimeout(console.log, 11000, p);