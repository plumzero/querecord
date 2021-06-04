
Cookie 是由 Web 服务器保存在用户计算机上的文本文件，其中包含一些用户信息，当用户下次访问该页面时，服务器从客户端的 Cookie 中读取相应的信息，为客户端制作特定的网页，使网页更具有亲和力与个性化。

Cookie 也可以记录单个用户访问网页的次数。

Cookie 是一个有大小限制的变量，单个服务器只能在服务器端存储最多 20 条信息，最大的 Cookie 值不能超过 4KB，超过限制，Web 浏览器会自动删除旧的 Cookie ，所以客户端不必担心 Cookie 会带来病毒。

Cookie 是与服务器域名相关联的，默认情况下 Cookie 的生存期是当浏览器关闭时被清空(注意，不是当用户准备离开这个页面的时候)，但可以用一个脚本程序改变这种情况，在用户关闭浏览器后使 Cookie 能够存储下来。

Cookie 分为临时 Cookie 和永久 Cookie ，通过属性设置可以创建、读取、删除 Cookie 等操作。

### Cookie 的属性

* name 属性
`name` 属性是 Cookie 中唯一的必选参数，可以通过 `document.cookie=name+value` 来创建一个 Cookie 对象。仅使用 `name=value` 创建的 Cookie 称为临时 Cookie，只为当前浏览器会话可用。

* expires 属性
`expires` 属性用来设置 cookie 在删除之前要在客户端计算机上保存多长时间。设置 expires 属性可以在浏览器会话之外维持 cookie，建立一个长久的 cookie 。如果不使用 expires 属性，则建立一个临时的 cookie，只在浏览器会话之间时使用。expires 的语法格式如下:
```js
    expires=date
```
`date` 时间的文本格式为格林尼治标准时间，表示方式为 `Fri Jun 4 21:37:18 PST 2021`。

对时间的设置可以通过 `Date()` 对象来进行操作。可以通过 Date() 对象中的 `get()` 和 `set()` 方法指定 cookie 中的有效时间。例如将 cookie 有效期设置为 30 天:
```js
    var time = new Date();
    time.setDate(time.getDate() + 30)
    document.cookie = encodeURI("user=tom") + "; expires=" + time.toUTCString();
```
`encodeURI()` 函数可把字符串作为 URI 进行编码。对 Date() 进行 `toUTCString()`，将时间转化，确保时间为格林尼治标准时间。

也可以通过将时间设置为过去的时间来使 cookie 失效，达到删除 cookie 的目的，例如:
```js
    var time = new Date();
    time.setDate(time.getDate() - 30);
    document.cookie = encodeURI("user=tom") + "; expires=" + time.toUTCString();
```

* path 属性
`path` 属性决定 cookie 对于服务器上其他目录下所有页面都可用，使用方法:
```js
    path=value
```

* domain 属性
使用 path 属性使 cookie 在一个服务器中共享，而 `domain` 属性可以使 cookie 在一个域名中的多台服务器之间共享 cookie(注意不能在不同域名之间共享 cookie)。使用方法:
```js
    domain=域名
```
例如，如果服务器 javascript.js.com 与服务器 asp.js.com 之间共享 cookie，那么可以将 domain 的属性设置为 "domain=.js.com"。

* secure 属性
标准的 Internet 连接对于传输比较隐蔽的信息如信用卡号、密码等比较不够安全，通过使用 `secure` 属性表示只能使用 HTTPS 或其他安全协议的安全 Internet 连接来传输。使用方法:
```js
    secure=true|false
```
"secure=true" 表示使用安全协议进行传输信息。


### Cookie 的储存

[将表单提交的用户名和密码存储到cookie中](t/02_cookie_store.html)


### Cookie 的读取

Cookie 是由一个连续的字符串组成，如果 cookie 存储的时候进行了 encodeURI() 编码，在使用它们包含的数据之前必须使用 `decodeURI()` 方法解析该字符串。在 cookie 中各个参数之间使用分号和空格进行连接，可以使用 `split()` 方法将每个属性值分离开，存储到数组中。

[cookie的获取示例](t/02_cookie_fetch.html)
