
import protoLoader from '@grpc/proto-loader';
import grpc from '@grpc/grpc-js';

const options = {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
}

const echoProtoDef = protoLoader.loadSync('echo_service.proto', options);
const echo_service = echoProtoDef['hello.EchoService'];

var echo_server = new grpc.Server();

echo_server.addService(echo_service, {
    echo: function(call, callback) {
        call.sendMetadata(call.metadata);
        if (call.request.value === 'error') {
            var status = {
                code: 2,
                message: 'test status message'
            };
            status.metadata = call.metadata;
            callback(status, null);
            return;
        }
        console.log('received message', call.request);
        // callback(null, call.request);
        callback(null, call.request = { value: 'world', value2: 5678 });
    }
});

var server_credentials = grpc.ServerCredentials.createInsecure();

echo_server.bindAsync('localhost:32000', server_credentials, (err, port) => {
    if (err) {
        console.log('start server failed');
        return;
    }

    echo_server.start();
    console.log('=== start success ===');
});
