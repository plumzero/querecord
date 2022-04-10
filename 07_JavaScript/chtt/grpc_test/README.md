
### 依赖安装

- npm install @grpc/grpc-js@1.4.4
- npm install @grpc/proto-loader@0.5.5

### 过程中的问题

谨记，对于 Node.js 来说，调试即打印，打印即调试。

1. 函数未定义
   
按照官方 gitlab 项目中的测试文件编写自己的测试时，报如下错误:
```js
    import grpc from '';

    const serverGrpc = grpc.server;
    var echo_server = new serverGrpc.Server();
                                    ^

    TypeError: Cannot read property 'Server' of undefined
```
这个时候将引入的模块变量打印出来，发现 Server 定义在 grpc 中，而不是 grpc.server 中。官网的测试代码没有及时更新了。


2. 将模块中的变量打印出来

下列代码会执行出错:
```js
    const echo_service = echoProtoDef.hello.EchoService;
```

将 echoProtoDef.hello 打印出来，发现 undefined 。

将 echoProtoDef 打印出来，如下:
```js
echoProtoDef:  {
  'hello.EchoMessage': {
    format: 'Protocol Buffer 3 DescriptorProto',
    type: {
      field: [Array],
      nestedType: [],
      enumType: [],
      extensionRange: [],
      extension: [],
      oneofDecl: [],
      reservedRange: [],
      reservedName: [],
      name: 'EchoMessage',
      options: null
    },
    fileDescriptorProtos: [
      <Buffer 0a 0b 68 65 6c 6c 6f 2e 70 72 6f 74 6f 12 05 68 65 6c 6c 6f 22 2c 0a 0b 45 63 68 6f 4d 65 73 73 61 67 65 12 0d 0a 05 76 61 6c 75 65 18 01 20 01 28 09 ... 87 more bytes>
    ]
  },
  'hello.EchoService': {
    Echo: {
      path: '/hello.EchoService/Echo',
      requestStream: false,
      responseStream: false,
      requestSerialize: [Function: serialize],
      requestDeserialize: [Function: deserialize],
      responseSerialize: [Function: serialize],
      responseDeserialize: [Function: deserialize],
      originalName: 'echo',
      requestType: [Object],
      responseType: [Object]
    }
  }
}
```
改成如下:
```js
    const echo_service = echoProtoDef['hello.EchoService'];
```
通过。
