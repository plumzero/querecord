
import _ from 'lodash';

let accounts = [ 1234, 3456 ];
let instrumentIDs = [ 'IF2206', 'ID2206' ];

let array = [
    {
        id: 1234,
        positions: [
            {
                instrumentID: 'IF2206'
            },
            {
                instrumentID: 'IF2208'
            }
        ]
    },
    {
        id: 2345,
        positions: [
            {
                instrumentID: 'IF2208'
            },
            {
                instrumentID: 'ID2206'
            }
        ]
    },
    {
        id: 3456,
        positions: [
            {
                instrumentID: 'IF2206'
            },
            {
                instrumentID: 'ID2206'
            }
        ]
    },
    {
        id: 4567,
        positions: [
            {
                instrumentID: 'IC2206'
            }
        ]
    }
];

let data = array.filter(item => accounts.find(ele => ele === item.id) !== undefined);

for (let element of data) {
    element.positions = element.positions.filter(item => instrumentIDs.find(ele => ele === item.instrumentID) !== undefined);
}

for (let element of data) {
    console.log(JSON.stringify(element));
}

// 原生不支持这种过滤方法
// let filter = array.filter({ id: 4567 });
// console.log('filter:', filter);

let filter2 = _.filter(array, { id: 4567 });
console.log('filter2:', filter2);
