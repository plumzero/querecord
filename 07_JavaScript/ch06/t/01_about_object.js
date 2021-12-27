
// "use strict";

console.log("--- 数据属性 ---");
{
    let person = {};
    Object.defineProperty(person, "name", {
        writable: false,
        value: "Nicholas"
    });

    console.log(person.name);
    person.name = "Greg";
    console.log(person.name);
}

console.log("--- 访问器属性 ---");
{
    let book = {
        year_: 2017,
        edition: 1
    };

    Object.defineProperty(book, "year", {
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
    console.log(book.edition);
}

console.log("--- 定义多个属性 ---");
{
    let book = {};
    Object.defineProperties(book, {
        year_: {
            value: 2017
        },
        edition: {
            writable: true,
            value: 1
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
    book.year = 2018;
    console.log(book.edition);
}

console.log("--- 读取属性的特性 ---");
{
    let book = {};
    Object.defineProperties(book, {
        year_: {
            value: 2017
        },
        edition: {
            value: 1
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

    let descriptor = Object.getOwnPropertyDescriptor(book, "year_");
    console.log(descriptor.value);
    console.log(descriptor.configurable);
    console.log(typeof descriptor.get);

    let descriptor2 = Object.getOwnPropertyDescriptor(book, "year");
    console.log(descriptor2.value);
    console.log(descriptor2.enumerable);
    console.log(typeof descriptor2.get);
}

console.log("--- Object.getOwnPropertyDescriptors ---");
{
    let book = {};
    Object.defineProperties(book, {
        year_: {
            value: 2017
        },
        edition: {
            value: 1
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

    console.log(Object.getOwnPropertyDescriptors(book));
}

console.log("--- 对象标识及相等判定 === ---");
{
    // 这些是 === 符合预期的情况
    console.log(true === 1);    // false
    console.log({} === {});     // false
    console.log("2" === 2);     // false
    
    // 这些情况在不同的 JavaScript 引擎中表现不同，但仍被认为相等
    console.log(+0 === -0);     // true
    console.log(+0 === 0);      // true
    console.log(-0 === 0);      // true

    // 要确定 NaN 的相等性，必须使用极为讨厌的 isNaN()
    console.log(NaN === NaN);   // false
    console.log(isNaN(NaN));    // true
    
}

console.log("--- 对象标识及相等判定 Object.is() ---");
{
    console.log(Object.is(true, 1));    // false
    console.log(Object.is({}, {}));     // false
    console.log(Object.is("2", 2));     // false

    // 正确的 0、-0、+0 相等/不等判定
    console.log(Object.is(+0, -0));     // false
    console.log(Object.is(+0, 0));      // true
    console.log(Object.is(-0, 0));      // false

    // 正确的 NaN 相等判定
    console.log(Object.is(NaN, NaN));   // true
}