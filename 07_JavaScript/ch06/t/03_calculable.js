
const nameKey = 'name';
const ageKey = 'age';
const jobKey = 'job';
let person = {
    [nameKey]: 'Matt',
    [ageKey]: 27,
    [jobKey]: 'Software engineer'
};

console.log(person);

let uniqueToken = 0;
function getUniqueKey(key) {
    return `${key}_${uniqueToken++}`;
}

let person2 = {
    [getUniqueKey(nameKey)]: 'Matt',
    [getUniqueKey(ageKey)]: 27,
    [getUniqueKey(jobKey)]: 'Software engineer'
};
console.log(person2);