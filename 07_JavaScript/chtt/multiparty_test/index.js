
import express from 'express';
import serveIndex from 'serve-index';
import serveStatic from 'serve-static';
import multiparty from 'multiparty';
import finalhandler from 'finalhandler';

var app = express();

app.post('/upload', function(req, res) {
    var form = new multiparty.Form();
    form.encoding = 'utf-8';
    form.uploadDir = './htdocs/upfile';
    form.maxFilesSize = 4 * 1024 * 1024;
    form.parse(req, function(err, fields, files) {
        if (err) {
            console.log('parse error: ' + err);
        } else {
            console.log('parse files: ' + JSON.stringify(files));
        }
        res.writeHead(200, {'content-type': 'text/plain;charset=utf-8'});
        res.write('received upload');
        res.end();
    });
});

var serve = serveStatic('./htdocs');
app.use('/', serveIndex('./htdocs', {'icons': true}));

app.get('/*', function(req, res) {
    serve(req, res, finalhandler(req, res));
});

console.log('would listen on port 3000');
app.listen(3000);
