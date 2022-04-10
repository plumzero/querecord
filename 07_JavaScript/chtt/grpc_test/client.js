
import protoLoader from '@grpc/proto-loader';
import anyGrpc from '@grpc/grpc-js';

const options = {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
}

var insecureCreds = anyGrpc.credentials.createInsecure();

const clientOptions = {
    'grpc.max_send_message_length': -1,
    'grpc.max_receive_message_length': -1
};

const echoProtoDef = protoLoader.loadSync('echo_service.proto', options);
const EchoClient = anyGrpc.loadPackageDefinition(echoProtoDef).hello.EchoService;
const client = new EchoClient('localhost:32000', insecureCreds, clientOptions);

let message = {
    value: "world",
    value2: 1234
};

client.echo(message, (err, res) => {
    if (err) {
        console.log('error:', err);
    } else {
        console.log('success', res);
    }
});
