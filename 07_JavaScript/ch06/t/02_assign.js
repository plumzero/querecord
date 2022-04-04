
let dest, src, result;

// 简单复制
dest = {};
src = { id: 'src' };

result = Object.assign(dest, src);

console.log(dest === result);   // true
console.log(dest !== src);      // false
console.log(result);
console.log(dest);

// 多个源对象
dest = {};
result = Object.assign(dest, { a: 'foo' }, { b: 'bar' });
console.log(result);

// 获取函数与设置函数
dest = {
    set a(val) {
        console.log(`Invoked dest setter with param ${val}`);
    }
};
src = {
    get a() {
        console.log('Invoked src getter');
        return 'foo';
    }
};
Object.assign(dest, src);
console.log(dest);