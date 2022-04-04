
let book = {
    year_: 2017,        // 私有成员
    edition: 1          // 公共成员
};
Object.defineProperty(book, 'year', {
    get() {
        return this.year_;
    },
    set(newValue) {
        if (newValue > 2017) {
            this.year_ = newValue;
            this.edition += newValue - 2017;
        }
    }
});
book.year = 2018;
console.log(book.edition);  // 2

// console.log(book.year_); // 2018
