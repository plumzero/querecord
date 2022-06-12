
// 将 false undefined null 0 从数组中移除

let arr = [ 1, 3, 'Libra', '7', false, undefined, null, 0 ];
let res = arr.filter(Boolean);
console.log(res);
