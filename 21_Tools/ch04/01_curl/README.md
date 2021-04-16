
### 一些高级使用

- 双向认证调试(-v)
  ```shell
    curl -v https://192.168.10.130:445 --cacert sm2.ca.crt.pem --cert sm2.client.crt.pem --key sm2.client.pvk.pem
  ```

- 发送不安全(-k)GET请求，除了获取内容之外还有响应头信息(-i)，将cookie写入cookie.txt(--cookie-jar)，将响应头信息写入header.txt(--dump-header)
  ```shell
    curl -X GET -k -i www.baidu.com --cookie-jar cookie.txt --dump-header header.txt
  ```

- 发送 GET 请求，超时返回(--connect-timeout)，命令执行代码写入到code.c
  ```shell
    curl -X GET -k -i --connect-timeout 5 www.google.com --libcurl code.c
  ```

- 发送POST请求及参数 注意参数不等同于表单
  ```shell
    curl -X POST api.juheapi.com/japi/toh --data "key=4be7e7f0f6b180cc3677ddb0b94abfcb&month=10&day=1&v=1.0" --progress-bar
  ```

- 发送POST请求及表单
  ```shell
    curl -X POST 192.168.10.137/dir/3.php --form username=ultraboy --form userage=20394
    curl -X POST 192.168.10.137/dir/3.php -d'username=ultraboy&userage=20394'
  ```

- 指定`Content-Type`
  ```shell
    curl -X POST 192.168.10.137/dir/3.php -H "Content-Type:application/json" -d'{"username" : "ultraboy", "userage" : "20394"}'
  ```

- 测试网页返回值
  ```shell
    curl -o /dev/null -s -w %{http_code} www.baidu.com
  ```

- 下载文件
  ```shell
    curl -o nginx-1.14.0.tar.gz http://nginx.org/download/nginx-1.14.0.tar.gz
  ```

- 断点续传
  ```shell
    curl -C -O ftp://192.168.10.137/test.tar.gz
  ```

- 上传文件
  ```shell
    curl -T upload.tar.gz -u 用户名:密码 ftp://192.168.10.137/
  ```
