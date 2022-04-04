
let book = {};
Object.defineProperties(book, {
    year_: {
        value: 2017,
        writable: true      // 在调用 Object.defineProperties() 时，configurable、enumerable 和 writable 的值如果不指定，则都默认为 false 。如果想要可写，则 writable 应设置为 true
    },
    edition: {
        value: 1,
        writable: true
    },
    year: {
        get() {
            return this.year_;  // book.year_
        },
        set(newValue) {
            if (newValue > 2017) {
                this.year_ = newValue;
                this.edition += newValue - 2017;
            }
        }
    }
});

book.year = 2018;
console.log(book.edition);  // 2

// console.log(book.year_); // 2018
