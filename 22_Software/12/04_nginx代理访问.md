
编辑 nginx.conf 配置文件

1.一处去掉注释
  ```sh
    log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';

    access_log  logs/access.log  main;
  ```

2.二处加上 `index.php` 文件
  ```sh
    location / {
        root   html;
        index  index.php index.html index.htm;
    }
  ```

3.去掉注释并修改
  ```sh
    location ~ \.php$ {
        root           html;
        fastcgi_pass   127.0.0.1:9000;
        fastcgi_index  index.php;
    #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
    #    include        fastcgi_params;
        include        fastcgi.conf;
    }
  ```
  之后重启 nginx 。

4.测试。在 `/usr/local/nginx/html` 下创建 `index.php` 文件，输入如下内容:
  ```php
    <?
        phpinfo();
    ?>
  ```
  在浏览器上输入如下 url 访问:
  ```sh
    ip:80/index.php
  ```
