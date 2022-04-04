
// 创建不可配置属性
let person = {};
Object.defineProperty(person, "name", {
    configurable: false,
    value: 'Nicholas'
});
console.log(person.name);       // 'Nicholas'
delete person.name;
console.log(person.name);       // 'Nicholas'
