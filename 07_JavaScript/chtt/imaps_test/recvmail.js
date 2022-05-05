
import imaps from 'imap-simple';

let config = {
    imap: {
        user: 'shouquan@qq.com',
        password: 'shou-quan-ma',
        host: 'imap.qq.com',
        port: 993,
        tls: true,
        authTimeout: 3000
    }
};

async function main() {
    let connection = await imaps.connect(config);
    await connection.openBox('INBOX');

    let delay = 3 * 3600 * 1000;
    let past = new Date();
    past.setTime(Date.now() - delay);
    past = past.toISOString();

    console.log('past: ', past);

    let searchCriteria = [ 'SEEN', [ 'SINCE', past ] ];   // 查找自 <past> 时间点到现在为止的<未读邮件>  // ALL, UNSEEN, 
    let fetchOptions = { bodies: [ 'HEADER', 'HEADER.FIELDS (FROM TO SUBJECT DATE)' ], struct: true };    // 输出 4 个字段: FROM TO SUBJECT DATE
    // searchCriteria: ALL, UNSEEN, SEEN, 1:5
    // fetchOptions: HEADER, TEXT

    let messages = await connection.search(searchCriteria, fetchOptions);
    if (messages.length === 0) {
        console.log('no messages!');
        return;
    }

    console.log('total received %d messages', messages.length);

    for (let message of messages) {
        // console.log(message.attributes.uid, message.parts[0].body);
        // 将未读邮件转为已读
        connection.addFlags(message.attributes.uid, 'SEEN', (err) => {    // 只能将 <未读> 转为 <已读>，不能将 <已读> 转为 <未读>
            if (err) {
                console.log("邮箱转未读失败");
            }
        });

        // 获取收件人信息
        let mailFrom = message.parts.filter((part) => { return part.which === 'HEADER'; })[0].body.from;
        console.log('收件人信息: ', mailFrom);
 
        let parts = imaps.getParts(message.attributes.struct);

        parts = parts.filter((part) => {        // 筛选出带有附件的邮件
            return part.disposition && part.disposition.type.toUpperCase() === 'ATTACHMENT';
        });
        
        for (let part of parts) {
            let partData = await connection.getPartData(message, part);
            console.log('邮件主题: ', message.parts[0].body.subject[0]);
            console.log('接收时间: ', message.attributes.date);
            console.log('附件名称: ', part.disposition.params.filename);
            console.log('附件内容: ', partData);
            console.log('邮件发自: ', mailFrom);
        }
    }

    connection.imap.closeBox(true, (err) => { // Pass in false to avoid delete-flagged messages being removed
        if (err){
            console.log(err);
        }
    });
    connection.end();
}

main().catch(err => {
    console.error(err.message);
    process.exit(-1);
});
