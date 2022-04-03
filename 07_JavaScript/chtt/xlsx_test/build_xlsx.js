
import xlsx from 'node-xlsx';
import fs from 'fs';

const data = [
    [1, 2, 3],
    [true, false, null, 'sheetjs'],
    ['foo', 'bar', new Date('2014-02-19T14:30Z'), '0.3'],
    ['baz', null, 'qux'],
];

var buffer = xlsx.build([{name: 'mySheetName', data: data}]);

const writeStream = fs.createWriteStream("build_xlsx.xlsx");
writeStream.write(buffer);
writeStream.end();
