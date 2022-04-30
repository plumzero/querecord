
import express from 'express';
import process from 'process';

const app = express();

// 只解析 json，不接收其他扩展格式
app.use(express.json());
app.use(express.urlencoded({ limit: '1kb', extended: false }));

app.use(function (req, res, next) {
    console.log('req.url:', req.url);
    console.log('Content-Type:', req.get('Content-Type'));
    console.log('Content-Length:', req.get('Content-Length'));
    next();
});

// GET 方法测试: /user?ID=???
app.get('/user', function(req, res) {
    let message = 'Hi ' + req.query.ID + ', I got!';
    res.send(message);
});

// POST 方法测试
app.post('/user', function(req, res) {
    let message = 'Hi ' + req.body.firstName + ' ' + req.body.lastName + ', I got!';
    res.send(message);
});

const server = app.listen(8080, () => console.log('Server ready'))

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
