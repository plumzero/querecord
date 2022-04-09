
import redis from 'redis';

function Redis(args) {
    this.client_ = redis.createClient(args);

    this.client_.on('ready', function() {
        console.log('ready succes');
    });

    this.client_.on('connect', function() {
        console.log('connected succes');
    });
    
    this.client_.on('error', function(error) {
        console.error(error);
    });
}

Redis.prototype.close = function() {
    this.client_.end(true);
    console.log('redis closed');
}

Redis.prototype.exists = function(key) {
    return new Promise((resolve, reject) => {
        this.client_.exists(key, (err, res) => {
            if (err) {
                reject(err);
            } else {
                res !== 0 ? resolve(true) : resolve(false);
            }
        });
    });
}

Redis.prototype.del = function(key) {
    return new Promise((resolve, reject) => {
        this.client_.del(key, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve(true);
            }
        });
    });
}

Redis.prototype.set = function(key, val) {
    return new Promise((resolve, reject) => {
        this.client_.set(key, val, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve(true);
            }
        });
    });
}

Redis.prototype.get = function(key) {
    return new Promise((resolve, reject) => {
        this.client_.get(key, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

// hash
Redis.prototype.hexists = function(key, field) {
    return new Promise((resolve, reject) => {
        this.client_.hexists(key, field, (err, res) => {
            if (err) {
                reject(err);
            } else {
                res !== 0 ? resolve(true) : resolve(false);
            }
        });
    });
}

Redis.prototype.hset = function(key, field, val) {
    return new Promise((resolve, reject) => {
        this.client_.hset(key, field, val, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve(true);
            }
        })
    });
}

Redis.prototype.hget = function(key, field) {
    return new Promise((resolve, reject) => {
        this.client_.hget(key, field, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

Redis.prototype.hdel = function(key, field) {
    return new Promise((resolve, reject) => {
        this.client_.hdel(key, field, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve(true);
            }
        });
    });
}

Redis.prototype.hmset = function(key, val) {
    if ((Array.isArray(val) && val.length === 0) || JSON.stringify(val) === '{}') {
        return new Promise((resolve, reject) => {
            this.client_.del(key, (err) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(true);
                }
            });
        });
    }

    return new Promise((resolve, reject) => {
        for (let item in val) {
            this.client_.hmset(key, item, JSON.stringify(val[item]), (err) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(true);
                }
            });
        }
    });
}

// list
Redis.prototype.rpush = function(key, val) {
    return new Promise((resolve, reject) => {
        this.client_.rpush(key, val, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve(true);
            }
        });
    });
}

Redis.prototype.lindex = function(key, index) {
    return new Promise((resolve, reject) => {
        this.client_.lindex(key, index, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

Redis.prototype.lrange = function(key, begin, end) {
    return new Promise((resolve, reject) => {
        this.client_.lrange(key, begin, end, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

Redis.prototype.llen = function(key) {
    return new Promise((resolve, reject) => {
        this.client_.llen(key, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

Redis.prototype.lrem = function(key, count, val) {
    return new Promise((resolve, reject) => {
        this.client_.lrem(key, count, val, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

export default Redis;
