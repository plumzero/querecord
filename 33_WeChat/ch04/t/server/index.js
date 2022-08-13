
import express from 'express';
import axios from 'axios';
import process from 'process';

const app = express();

// 只解析 json，不接收其他扩展格式
app.use(express.json());
app.use(express.urlencoded({ limit: '1kb', extended: false }));

// 服务器所有
let _appid = '';
// 服务器所有
let _secret = '';
// 用于保存从微信接口服务中获取到的 openid
let _user = { openid: '' };

// 为了安全，appid 和 secret 参数以命令行参数传入
_appid = process.argv[2]
_secret = process.argv[3]
console.log('appid: ', process.argv[2])
console.log('secret: ', process.argv[3])

app.use(function (req, res, next) {
    next();
});

// 如果不使用 await ，将会陷入反复回调之中

// 请求微信接口服务: 用于根据 code 获取 openid
const getOpenid = async(code) => {
    let param = {
        url: 'https://api.weixin.qq.com/sns/jscode2session?appid=' + _appid + '&secret=' + _secret + '&js_code=' + code + '&grant_type=authorization_code'
    };
    let resp = await axios(param);

    console.log('发送参数:', param)

    console.log('http 返回:', resp.status, resp.statusText)
    console.log('data 内容:', resp.data)

    console.log('用户 openid:', resp.data.openid);

    return resp.data.openid;
};

// 请求微信接口服务: 用于获取 access_token
const getAccessToken = async() => {
    let param = {
        url: 'https://api.weixin.qq.com/cgi-bin/token?grant_type=client_credential&appid=' + _appid + '&secret=' + _secret
    };
    let resp = await axios(param);

    console.log('访问令牌 access_token: ', resp.data.access_token);

    return resp.data.access_token;
};

// 与微信接口服务交互: 用于发送订阅消息
const sendTemplateMessage = async() => {
    let user = _user;
    let data = {
        touser: user.openid,
        template_id: 'UnSF_aMTiX4mBMFlTL7tio8O283jKMjS3VASgEUEiUE',
        page: 'index',
        data: {
            thing1: { value: '魔偶甜点·胶凝冰糕邮递员' },
            thing2: { value: '魔偶甜点城堡' },
            thing3: { value: '风云机巧城' },
            time5: { value: '2022-08-15' },
            character_string6: { value: ' 52404456 ' }
        }
    };
    let token = await getAccessToken();
    
    let param = {
        method: 'post',
        url: 'https://api.weixin.qq.com/cgi-bin/message/subscribe/send?access_token=' + token,
        data: data
    };
    let resp = await axios(param);

    console.log('流程走完', resp.data);
}

// 接收小程序发来的表单
app.post('/formsubmit', async function(req, res) {
    console.log('收到客户端提交的数据: ', req.body)
    // 获取用户的 openid
    let openid = await getOpenid(req.body.code);
    _user.openid = openid;
    // 向微信接口服务发送订阅消息，该消息会由后者推送给用户小程序
    await sendTemplateMessage();
});

app.post('/post', function(req, res) {
    let message = {};
    message.msg = 'post the world';
    console.log('req.body', req.body);
    res.send(message);
});

const server = app.listen(8000, () => console.log('Server ready'))

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
