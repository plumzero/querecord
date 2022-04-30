
import fs from 'fs';
import path from 'path';

// 列出指定路径下的所有目录
function listDirs(root) {
    var files = fs.readdirSync(root);
    var dirs = [];

    for (var i = 0, l = files.length; i < l; i++) {
        var file = files[i];
        if (file[0] !== '.') {
            var stat = fs.statSync(path.join(root, file));
            if (stat.isDirectory()) {
                dirs.push(file);
            }
        }
    }

    return dirs;
}

// 列出指定路径下的所有非目录文件
function listFiles(root) {
    var files = fs.readdirSync(root);
    var dirs = [];

    for (var i = 0, l = files.length; i < l; i++) {
        var file = files[i];
        if (file[0] !== '.') {
            var stat = fs.statSync(path.join(root, file));
            if (stat.isFile()) {
                dirs.push(file);
            }
        }
    }

    return dirs;
}

let dirs = listDirs('../');
console.log('dirs: ', dirs);

let files = listFiles('./');
console.log('files: ', files);
