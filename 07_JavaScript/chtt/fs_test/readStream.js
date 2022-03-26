
import fs from 'fs';
import readline from 'readline';

// npm init -y

async function main() {
    const readStream = fs.createReadStream("test.csv");
    const rl = readline.createInterface({
        input: readStream,
        crlfDelay: Infinity
    });
    for await (const line of rl) {
        let kvs = line.split(',');
        kvs.forEach((item, index, array) => {
            let kv = item.split(':');
            console.log("%s => %s", kv[0], kv[1]);
        });
    }
    rl.close();
}

main()
    .then(() => {})
    .catch(err => console.error(err));
