import Imap from 'imap';
import { inspect } from 'util';

var imap = new Imap({
    user: 'shou-quan@qq.com',
    password: 'shou-quan-ma',
    host: 'imap.qq.com',
    port: 993,
    tls: true,
    authTimeout: 3000,
    keepalive: true
});

imap.on('ready', function() {
    imap.openBox('INBOX', true, function(err, box) {
        if (err) throw err; // Promise reject
        let f = imap.seq.fetch('1:3', {
            bodies: 'HEADER.FIELDS (FROM TO SUBJECT DATA)',
            struct: true
        });
        f.on('message', function(msg, seqno) {
            console.log('Message $%d', seqno);
            let prefix = '(#' + seqno + ') ';
            msg.on('body', function(stream, info) {
                let buffer = '';
                stream.on('data', function(chunk) {
                    buffer += chunk.toString('utf8');
                });
                stream.on('end', function() {
                    console.log(prefix + 'Parsed header: %s', inspect(Imap.parseHeader(buffer)));
                });
            });
            msg.on('attributes', function(attrs) {
                console.log(prefix + 'Attributes: %s', inspect(attrs, false, 1));
            });
            msg.on('end', function() {
                console.log(prefix + 'Finished');
            });
        });
        f.on('error', function(err) {
            console.log('Fetch error: ' + err);
        });
        f.on('end', function() {
            console.log('Done fetching all messages!');
            imap.end()
        });
    });
});

imap.on('error', function(err) {
    console.log(err);
});

imap.on('end', function() {
    console.log('Connected ended');
});

imap.connect();
