
import xlsx from 'node-xlsx';
import fs from 'fs';

const data = [
    [1, 2, 3],
    [true, false, null, 'sheetjs'],
    ['foo', 'bar', new Date('2014-02-19T14:30Z'), '0.3'],
    ['baz', null, 'qux'],
];

const options = { '!cols': [{wch: 6}, {wch:7}, {wch:10}, {wch: 20}] };

var buffer = xlsx.build([{name: 'mySheetName', data: data}], options);

const writeStream = fs.createWriteStream("custom_column_width.xlsx");
writeStream.write(buffer);
writeStream.end();
