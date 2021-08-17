const { SSL_OP_EPHEMERAL_RSA } = require("constants")

function myTest() {
    setTimeout(() => {
        console.log('after ')
    }, 1000)

    var sum = 0
    for (var i = 0; i < 40000000; i++) {
        sum += i
    }

    console.log(' before ')
}

myTest()