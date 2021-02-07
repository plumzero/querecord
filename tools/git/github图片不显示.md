
markdown 文件支持多种图片格式，如 .jpg .png .svg 等，也支持 css 样式。

但本地 markdown 文件提交到 github 上就无法显示图片了...

解决办法如下:

- 以管理员权限修改hosts
  ```
    C:\Windows\System32\drivers\etc\hosts
  ```

- 在文件末尾添加如下内容
  ```
    # GitHub Start 
    192.30.253.112    Build software better, together 
    192.30.253.119    gist.github.com
    151.101.184.133    assets-cdn.github.com
    151.101.184.133    raw.githubusercontent.com
    151.101.184.133    gist.githubusercontent.com
    151.101.184.133    cloud.githubusercontent.com
    151.101.184.133    camo.githubusercontent.com
    151.101.184.133    avatars0.githubusercontent.com
    151.101.184.133    avatars1.githubusercontent.com
    151.101.184.133    avatars2.githubusercontent.com
    151.101.184.133    avatars3.githubusercontent.com
    151.101.184.133    avatars4.githubusercontent.com
    151.101.184.133    avatars5.githubusercontent.com
    151.101.184.133    avatars6.githubusercontent.com
    151.101.184.133    avatars7.githubusercontent.com
    151.101.184.133    avatars8.githubusercontent.com

     # GitHub End
  ```

- 刷新或重新加载 github 网页
