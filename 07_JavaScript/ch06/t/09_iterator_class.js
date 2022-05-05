
class Person {
    constructor(arr) {
        this.nicknames = arr;
    }

    [Symbol.iterator]() {
        return this.nicknames.entries();
    }
}

let p1 = new Person([ 'Jack', 'Jake', 'J-Dog' ]);
let p2 = new Person([ 'Lily', 'Lucy', 'Lilei' ]);

for (let [idx, nickname] of p1) {
    console.log(idx, nickname);
}

for (let [idx, nickname] of p2) {
    console.log(idx, nickname);
}
