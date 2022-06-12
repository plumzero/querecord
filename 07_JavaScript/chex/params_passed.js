
let required = () => {
    throw new Error('param is required');
};

let test = (param = required()) => {
    console.log(param);
};

test('hello world');
