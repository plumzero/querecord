
import axios from 'axios';

const client = axios.create({
    baseURL: 'http://127.0.0.1:8080',
    timeout: 1000,
    headers: { 'Content-Type': 'application/json' }
});

client.interceptors.request.use(function (config) {
    console.log('config.url:', config.url);
    console.log('config.method:', config.method);
    return config;
}, function (error) {
    return Promise.reject(error);
});

client.interceptors.response.use(function(response) {
    console.log('response.status:', response.status);
    console.log('response.data:', response.data);
    return response;
}, function (error) {
    return Promise.reject(error);
});

client.get('/user?ID=12345')
    .then(function(response) {  // when success
        console.log("status: ", response.status);
        console.log("statusText: ", response.statusText);
        console.log("data: ", response.data);
    })
    .catch(function(error) {    // while error 
        console.error("status: ", error);
    })
    .then(function() {          // always executed
        console.log('=== ended ===');
    });
