
import GrpcClient from './grpc.js';

async function main() {
    let gc = new GrpcClient('localhost:32000', 'echo_service.proto');

    let res = await gc.echo({ value: 'hello', value2: 1234 });
    console.log(res);

    return '=== ok ===';
}

main()
    .then((res) => console.log(res))
    .catch((err) => console.log(err));
