
'use strict';

function makeKing(name = 'Henry', numerals = 'VIII') {
    return `King ${name} ${numerals}`;
}

console.log(makeKing());
console.log(makeKing('Louis'));
console.log(makeKing(undefined, 'VI'));
