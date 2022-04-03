
import xlsx from 'node-xlsx';
import fs from 'fs';

const dataSheet1 = [
    [1, 2, 3],
    [true, false, null, 'sheetjs'],
    ['foo', 'bar', new Date('2014-02-19T14:30Z'), '0.3'],
    ['baz', null, 'qux']
];
const dataSheet2 = [
    [4, 5, 6],
    [7, 8, 9, 10],
    [11, 12, 13, 14],
    ['baz', null, 'qux']
];
const range = {s: {c: 0, r: 0}, e: {c: 0, r: 3}}; // A1:A4
const sheetOptions = {'!merges': [ range ]};

var buffer = xlsx.build([{name: "myFirstSheet", data: dataSheet1}, {name: "mySecondSheet", data: dataSheet2, options: sheetOptions}]); // Returns a buffer

const writeStream = fs.createWriteStream("span_multi_rows_in_second_sheet.xlsx");
writeStream.write(buffer);
writeStream.end();
