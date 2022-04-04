
    console.log(Object.is(true, 1));        // false
    console.log(Object.is({}, {}));         // false
    console.log(Object.is("2", 2));         // false

    console.log(Object.is(+0, -0));         // false
    console.log(Object.is(+0, 0));          // true
    console.log(Object.is(-0, 0));          // false

    console.log(Object.is(NaN, NaN));       // true