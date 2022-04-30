
import axios from 'axios';

axios.get('http://www.baidu.com')
    .then(function (response) {
        // handle success
        console.log(response.status);
    })
    .catch(function (error) {
        // handle error
        console.log(error);
    })
    .then(function () {
        // always executed
    });
