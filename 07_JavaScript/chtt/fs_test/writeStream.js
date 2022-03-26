
import fs from 'fs';

// npm init -y

async function main() {
    const writeStream = fs.createWriteStream("test.csv");
    writeStream.on('error', (err) => {
        console.log('写入时异常', err);
    });
    writeStream.on('open', (fd) => {
        console.log('文件描述符打开', fd);
    });
    writeStream.on('finish', () => {
        console.log('写入完成');
    });
    writeStream.on('close', () => {
        console.log('关闭文件');
    });

    for (let i = 0; i < 10; i++) {
        let str = (i).toString().padStart(2, '0');
        let fmt_string = `id:${i},str:${str}\n`;
        writeStream.write(fmt_string);
    }

    writeStream.end();
}

main()
    .then(() => {})
    .catch(err => console.error(err));
