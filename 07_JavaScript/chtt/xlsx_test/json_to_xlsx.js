
import xlsx from 'node-xlsx';
import fs from 'fs';

const obj = JSON.parse(fs.readFileSync('json_to_xlsx.json'));
const buffer = xlsx.build(obj);

const writeStream = fs.createWriteStream("json_to_xlsx.xlsx");
writeStream.write(buffer);
writeStream.end();
