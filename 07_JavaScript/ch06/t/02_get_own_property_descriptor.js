
let book = {};
Object.defineProperties(book, {
    year_: {
        value: 2017
    },
    edition: {
        value: 1,
    },
    year: {
        get() {
            return this.year_;
        },
        set(newValue) {
            if (newValue > 2017) {
                this.year_ = newValue;
                this.edition += newValue - 2017;
            }
        }
    }
});

let descriptor_access = Object.getOwnPropertyDescriptor(book, 'year_');
console.log(descriptor_access.value);
console.log(descriptor_access.configurable);
console.log(typeof descriptor_access.get);
let descriptor_data = Object.getOwnPropertyDescriptor(book, 'year');
console.log(descriptor_data.value);
console.log(descriptor_data.enumerable);
console.log(typeof descriptor_data.get);
