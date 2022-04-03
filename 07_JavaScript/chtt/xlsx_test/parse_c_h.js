
import xlsx from 'node-xlsx';
import fs from 'fs';

// parse a buffer
const sheets = xlsx.parse(fs.readFileSync('parse_c_h.xlsx'));
console.log('sheets.length=%s', sheets.length);
for (const sheet of sheets) {
    console.log('表名: %s', sheet.name);
    console.log('行数: %d', sheet.data.length)
    for (let i = 0; i < sheet.data.length; i++) {
        let row = '第 ' + i + ' 行: ';
        for (let j = 0; j < sheet.data[i].length; j++) {
            row += sheet.data[i][j] + ', ';
        }
        console.log(row);
    }
}

// 第一个表调整为矩阵
let rows = {};
let cols = {};
let sheet = sheets[0];
for (let i = 0; i < sheet.data.length; i++) {
    rows[sheet.data[i][0]] = i;
}
console.log(rows);
for (let j = 0; j < sheet.data[0].length; j++) {
    cols[sheet.data[0][j]] = j;
}
console.log(cols);

let matrix = sheet.data;
console.log('行%d列%d: %f', 1, 2, matrix[1][2]);
console.log('行%d列%d: %f', 2, 5, matrix[2][5]);

console.log('%s行%s列: %f', 'c', '1983', matrix[rows['c']][cols['1983']]);
console.log('%s行%s列: %f', 'h', '1986', matrix[rows['h']][cols['1986']]);
