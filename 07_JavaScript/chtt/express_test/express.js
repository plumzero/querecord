
import express from 'express';
import process from 'process';

const app = express();

// 只解析 json，不接收其他扩展格式
app.use(express.json());
app.use(express.urlencoded({limit: '50mb', extended: false}));

app.use(function (req, res, next) {
    console.log('req.url:', req.url);
    console.log('Content-Type:', req.get('Content-Type'));
    console.log('Content-Length:', req.get('Content-Length'));
    next();
});

app.get('/get', function(req, res) {
    let message = {};
    message.msg = 'get the world';
    console.log('req.body', req.body);
    res.send(message);
});

app.post('/post', function(req, res) {
    let message = {};
    message.msg = 'post the world';
    console.log('req.body', req.body);
    res.send(message);
});

const server = app.listen(3000, () => console.log('Server ready'))

process.on('SIGTERM', () => {
    server.close(() => {
        console.log('Process terminated')
    })
})

process.on('SIGINT', () => {
    server.close(() => {
        console.log('Process interrupt')
    })
})
