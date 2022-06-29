
import json2csv from 'json2csv';

const { Parser } = json2csv;

const myCars = [
    {
      car: 'Audi',
      price: 40000,
      color: 'blue',
    },
    {
      car: 'BMW',
      price: 35000,
      color: 'black',
    },
    {
      car: 'Porsche',
      price: 60000,
      color: 'green',
    },
];

// 默认导出(导出全部)
{
    console.log('=== 默认导出(导出全部) ===');
    const json2csvParser = new Parser();
    const csv = json2csvParser.parse(myCars);
    
    console.log(csv);
}

// 特定列导出
{
    console.log('=== 特定列导出 ===');
    const fields = ['car', 'color'];

    const json2csvParser = new Parser({ fields });
    const csv = json2csvParser.parse(myCars);
    
    console.log(csv);
}

// 特定序导出
{
    console.log('=== 特定序导出 ===');
    const fields = ['car', 'color', 'price'];

    const json2csvParser = new Parser({fields});
    const csv = json2csvParser.parse(myCars);
    
    console.log(csv);
}

// 自定义头
{
    console.log('=== 自定义头 ===');
    const fields = [
        {
            label: '名称',
            value: 'car',
        },
        {
            label: '外观',
            value: 'color',
        },
        {
            label: '价格',
            value: 'price',
        },
    ];
      
      const json2csvParser = new Parser({ fields });
      const csv = json2csvParser.parse(myCars);
      
      console.log(csv);
}

// 自定义分隔符
{
    console.log('=== 自定义分隔符 ===');
    const json2csvParser = new Parser({ delimiter: '\t' });
    const tsv = json2csvParser.parse(myCars);
    
    console.log(tsv);
}

// 自定义格式化符
{
    console.log('=== 自定义格式化符 ===');
    const { formatters: { string: stringFormatter, number: numberFormatter } } = json2csv;
    
    const json2csvParser = new Parser({
        delimiter: ';',
        formatters: {
          string: stringFormatter({ quote: '*' }),
          number: numberFormatter({ separator: ',', decimals: 2 }),
        },
      });
      const csv = json2csvParser.parse(myCars);
      
      console.log(csv);
}