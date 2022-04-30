
import excel from 'node-excel-export';
import fs from 'fs';

const styles = {
    headerDark: {
        fill: {
            fgColor: {
                rgb: 'FF000000'
            }
        },
        font: {
            color: {
                rgb: 'FFFFFFFF'
            },
            sz: 14,
            bold: true,
            underline: true
        }
    },
    cellPink: {
        fill: {
            fgColor: {
                rgb: 'FFFFCCFF'
            }
        }
    },
    cellGreen: {
        fill: {
            fgColor: {
                rgb: 'FF00FF00'
            }
        }
    }
};

const heading = [
    [{ value: 'a1', style: styles.headerDark }, { value: 'b1', style: styles.headerDark }, { value: 'c1', style: styles.headerDark }],
    [ 'a2', 'b2', 'c2' ]
];

// 定义结构
const specification = {
    customer_name: {
        displayName: '客户',
        headerStyle: styles.headerDark,
        cellStyle: function (value, row) {
            return (row.status_id == 1) ? styles.cellGreen : { fill: {fgColor: {rgb: 'FFFF0000'}} };
        },
        width: 120      // 120 个像素
    },
    status_id: {
        displayName: '状态',
        headerStyle: styles.headerDark,
        cellFormat: function (value, row) {
            return (value == 1) ? 'Active' : 'Inactive';
        },
        width: '10'     // 10 个字符
    },
    note: {
        displayName: '说明',
        headerStyle: styles.headerDark,
        cellStyle: styles.cellPink,
        width: 220
    }
};

const dataset = [
    { customer_name: 'IBM', status_id: 1, note: 'some text', misc: 'not shown' },
    { customer_name: 'HP',  status_id: 0, note: 'some text' },
    { customer_name: 'MS',  status_id: 0, note: 'some text', misc: 'not shown' }
];

const merges = [
    { start: { row: 1, column: 1 }, end: { row: 1, column: 10 } },
    { start: { row: 2, column: 1 }, end: { row: 2, column: 5 } },
    { start: { row: 2, column: 6 }, end: { row: 2, column: 10 } }
];

const report = excel.buildExport(
    [
        {
            name: 'Report',                 // sheet name
            heading: heading,               // 行数组
            merges: merges,                 // 单元格
            specification: specification,   // 表格结构
            data: dataset                   // 表格数据
        }
    ]
);

fs.writeFileSync('write.xlsx', report);
