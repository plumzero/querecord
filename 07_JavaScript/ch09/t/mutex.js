
// 互斥锁
function Mutex() {
    this._flag = true;
    this._resolve = null;
}

Mutex.prototype.lock = async function() {
    return new Promise((resolve) => {
        if (this._flag) {
            this._flag = false;
            resolve();
        } else {
            this._resolve = resolve;
        }
    });
};

Mutex.prototype.unlock = function() {
    this._flag = true;
    this._resolve && this._resolve();
};


// 读写锁 (一写多读/写优先)
function RWMutex() {
    this._wc = 0;
    this._r = [];       // 要处理的读锁队列
    this._q = [];       // 要等待的读锁队列
    this._w = null;
}

RWMutex.prototype.wLock = async function() {
    return new Promise((resolve) => {
        if (this._wc === 1) process.exit(-1);
        ++this._wc;
        if (this._r.length !== 0) {
            this._w = resolve;
        } else {
            resolve();
        }
    });
};

RWMutex.prototype.wUnlock = function() {
    this._w && this._w();
    this._wc = 0;
    this._r = this._r.concat(this._q);
    this._q = [];
    let len = this._r.length;   // 避免极端情况下出现读优先
    for (let i = 0; i < len; i++) {
        let x = this._r[i];
        if (x.resolve) {
            x.resolve();
        }
    }
};

RWMutex.prototype.rLock = async function(name) {
    return new Promise((resolve) => {
        if (this._r.find(item => item.name === name) !== undefined) {
            process.exit(-1);
        }
        if (this._wc === 1) {
            this._q.push({name, resolve});
        } else {
            this._r.push({name, resolve: null});
            resolve();
        }
    });
};

RWMutex.prototype.rUnlock = function(name) {
    let pos = this._r.findIndex(item => item.name === name);
    if (pos !== -1) {
        let ele = this._r[pos];
        if (ele.resolve) {
            ele.resolve();
        }
        this._r.splice(pos, 1);
    }
    if (this._wc === 0) {   // 如果不是写状态，则将所有的读锁放入到处理队列
        this._r = this._r.concat(this._q);
        this._q = [];
    } else {
        if (this._r.length === 0) {
            this._w && this._w();
        }
    }
};

export {
    Mutex,
    RWMutex
}