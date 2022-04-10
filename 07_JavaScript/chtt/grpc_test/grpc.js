
import protoLoader from '@grpc/proto-loader';
import grpc from '@grpc/grpc-js';

const options = {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
}

var insecureCreds = grpc.credentials.createInsecure();

const clientOptions = {
    'grpc.max_send_message_length': -1,
    'grpc.max_receive_message_length': -1
};

function GrpcClient(addr, proto) {
    const echoProtoDef = protoLoader.loadSync(proto, options);
    const EchoClient = grpc.loadPackageDefinition(echoProtoDef).hello.EchoService;

    this.client_ = new EchoClient(addr, insecureCreds, clientOptions);
}

GrpcClient.prototype.echo = function(message) {
    return new Promise((resolve, reject) => {
        this.client_.echo(message, (err, res) => {
            if (err) {
                reject(err);
            } else {
                resolve(res);
            }
        });
    });
}

export default GrpcClient;
