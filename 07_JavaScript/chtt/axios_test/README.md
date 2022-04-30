
axios 作为客户端，express 作为服务端进行测试。

npm install axios@0.21.0

npm install express@4.17.1

通过 `import axios from 'axios';` 语句会使用一个全局客户端，该全局客户端的默认发送端口为 80 。

使用也可以通过 `axios.create` 方法创建自己的客户端实例。
