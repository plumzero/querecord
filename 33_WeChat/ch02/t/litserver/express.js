
import express from 'express';
import process from 'process';

const app = express();

app.use(express.json());
app.use(express.urlencoded({ limit: '1kb', extended: false }));

app.use(function (req, res, next) {
    console.log('req.url:', req.url);
    console.log('req.query:', req.query);
    console.log('req.body:', req.body);
    console.log('Content-Type:', req.get('Content-Type'));
    console.log('Content-Length:', req.get('Content-Length'));
    next();
});

// http://192.168.xxx.xxx:3000/get?name=lumian
app.get('/get', function(req, res) {
    let message = {};
    message.msg = 'get the world';
    console.log('req.query:', req.query);
    console.log('req.body', req.body);
    res.send(message);
});

// http://192.168.xxx.xxx:3000/post
app.post('/post', function(req, res) {
    let message = {};
    message.msg = 'post the world';
    console.log('req.body', req.body);
    res.send(message);
});

var data = {
    name: '张三',
    gender: [
        { name: '男', value: '0', checked: true },
        { name: '女', value: '1', checked: false }
    ],
    skills: [
        { name: 'HTML', value: 'html', checked: true },
        { name: 'CSS', value: 'css', checked: true },
        { name: 'JavaScript', value: 'js', checked: false },
        { name: 'Photoshop', value: 'ps', checked: false }
    ],
    opinion: '测试'
};

app.get('/', (req, res) => {
    res.json(data);
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
