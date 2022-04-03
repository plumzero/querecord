
import xlsx from 'node-xlsx';
import fs from 'fs';

const data1 = [
    [1, 2, 3],
    [true, false, null, 'sheetjs'],
    ['foo', 'bar', new Date('2014-02-19T14:30Z'), '0.3'],
    ['baz', null, 'qux'],
];

const data2 = [
    [10, 20, 30],
    [true, false, 'sheetjs'],
    ['foo', 'bar', '0.3'],
    ['baz', 'qux'],
];

// {c: 0, r: 0} column: 0, row: 0
// {c: 0, r: 3} column: 0, row: 3
const range = {s: {c: 0, r: 0}, e: {c: 0, r: 3}};   // A1:A4
const options = {'!merges': [range]};

var buffer = xlsx.build([{name: 'mySheetName1', data: data1}, { name: 'mySheetName2', data: data2 }], options);

const writeStream = fs.createWriteStream("span_multi_rows_in_every_sheets.xlsx");
writeStream.write(buffer);
writeStream.end();
