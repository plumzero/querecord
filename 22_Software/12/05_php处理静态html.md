
静态文件 `helloworld.html`
```html
    <!DOCTYPE html>
    <html>
    <head>  
        <meta http-equiv="content-type" content="text/html;charset=utf-8"/>  
        <title>上传用户信息</title>  
    </head>
    <body>
        <form enctype="multipart/form-data" method="post" action="helloworld.php">  
            <table>  
                <tr><td align="center" colspan="2"><font style="font-size:40px;font-family: 华文彩云;">字符串上传</font></td></tr>  
                <tr><td>请填写用户名~：</td><td><input type="text" name="username" value='xiaoming'/></td></tr>
                <tr><td>请填写年龄：</td><td><input type="text" name="userage" value=18 /></td></tr>
                <tr><td><input type="submit" name="submit "value="Submit me!"/></td><td></td></tr>  
            </table>
        </form>
    </body>
    </html>
```

php 脚本文件 `helloworld.php`
```php
    <?php
        $name = $_POST['username'];
        $age = $_POST['userage'];
        
        echo "username : ", $name, "\n";
        echo "userage : ", $age, "\n";
    ?>
```

将上面两个文件放置到 `/usr/local/nginx/html` 目录下。

在浏览器地址栏中访问 `ip:80/helloworld.html`,  点击 `Submit me!` 。
