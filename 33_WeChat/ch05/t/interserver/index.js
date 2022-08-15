
import express from 'express';
import axios from 'axios';
import process from 'process';
import crypto from 'crypto';
import WXBizDataCrypt from './WXBizDataCrypt.js';

const app = express();

// 只解析 json，不接收其他扩展格式
app.use(express.json());
app.use(express.urlencoded({ limit: '1kb', extended: false }));

const wx = {
    appid: '',      // AppId
    secret: ''      // AppSecret
};

var db = {
    session: {},    // 保存 openid 和 session_key 的会话信息
    user: {}        // 保存用户记录，如用户名、积分等数据
};

// 为了安全，appid 和 secret 参数以命令行参数传入
wx.appid = process.argv[2]
wx.secret = process.argv[3]
console.log('appid: ', wx.appid)
console.log('secret: ', wx.secret)

app.use(function (req, res, next) {
    next();
});

// 用户登录
app.post('/login', async function(req, res) {
    console.log('login code: ' + req.body.code);

    let param = {
        url: 'https://api.weixin.qq.com/sns/jscode2session?appid=' + wx.appid + '&secret=' + wx.secret + '&js_code=' + req.body.code + '&grant_type=authorization_code'
    };
    console.log('发送参数:', param)
    let resp = await axios(param);

    console.log('http 返回:', resp.status, resp.statusText)
    console.log('data 内容:', resp.data)

    let session = resp.data;
    if (session.openid) {
        let token = 'token_' + new Date().getTime();
        db.session[token] = session;
        // 保存用户记录，设置用户初始积分为 100
        if (!db.user[session.openid]) {
            db.user[session.openid] = { credit: 100 };
        }
        res.json({token: token});       // 将 token 响应给小程序
    }
});

// 查询积分
app.get('/credit', (req, res) => {
    let session = db.session[req.query.token];
    if (session && db.user[session.openid]) {
        res.json({credit: db.user[session.openid].credit});
    } else {
        res.json({err: '用户不存在，或未登录'})
    }
});

// token 过期?
app.get('/checkLogin', (req, res) => {
    let session = db.session[req.query.token];
    console.log('checklogin: ', session);
    res.json({is_login: session !== undefined});
});

// 在服务端解密
app.post('/userinfo', (req, res) => {
    var session = db.session[req.query.token];
    if (session) {
        // 使用 appid 和 session_key 解密 encryptedData
        let pc = new WXBizDataCrypt(wx.appid, session.session_key);
        let data = pc.decryptData(req.body.encryptedData, req.body.iv);
        console.log('解密后: ', data);
        // 校验 rawData 是否正确
        let sha1 = crypto.createHash('sha1');
        sha1.update(req.body.rawData + session.session_key);
        let signature2 = sha1.digest('hex');
        console.log('calc: ', signature2);
        console.log('recv: ', req.body.signature);
        res.json({pass: signature2 === req.body.signature2});
    } else {
        res.json({err: '用户不存在，或未登录'});
    }
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
