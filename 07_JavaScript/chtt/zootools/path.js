
import path from 'path';

let tpath = '/tmp/logs/20220422.log';

// 获取指定文件的所在目录
console.log('%s 所在的目录为 %s', tpath, path.dirname(tpath));

// 获取指定文件的文件短名称
console.log('%s 的文件短名称为 %s', tpath, path.basename(tpath));

// 获取指定文件的文件扩展名
console.log('%s 的文件扩展名为 %s', tpath, path.extname(tpath));

// 连缀文件
let dir = path.dirname(tpath);
console.log('%s 连缀文件 "test": %s', dir, path.join(dir, 'test'));

// 意会
console.log(path.resolve(tpath));
console.log(path.resolve(tpath, '..'));
console.log(path.resolve(tpath, 'test'));

// 当前文件所在目录
console.log(path.resolve(''));
