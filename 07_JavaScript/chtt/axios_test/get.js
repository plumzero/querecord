
import axios from 'axios';

const client = axios.create({
    baseURL: 'http://127.0.0.1:8080',
    timeout: 1000,
    headers: { 'Content-Type': 'application/json' }
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

// 简单的封装示例

async function getUser(userId) {
    try {
        let resp = await client.get('/user?ID=' + userId);
        console.log("status: ", resp.status);
        console.log("statusText: ", resp.statusText);
        console.log("data: ", resp.data);
    } catch(err) {
        console.error(error);
    }
}

getUser('54321').then(res => console.log('== success ==')).catch(err => console.error('== failed =='));
