
### Steps

```
vue create vue-axios-test
```

```
cd vue-axios-test
npm install axios vue-axios --save
```

```
npm run serve
```

### Targets

- 利用 vue.config.js 配置跨域
- 注意: 配置跨域后重启开发服务器才能生效

### Problems

```sh
    Watchpack Error (watcher): Error: ENOSPC: System limit for number of file watchers reached,
```

在 shell 会话中执行如下命令:
```sh
    sysctl fs.inotify.max_user_watches=524288
```

### About vue-axios

axios 本身是一个基于 promise 的 HTTP 客户端工具，vue-axios 针对 Vue 对 axios 进行了一层简单的封装。

vue-axios 中提供了一些常用快捷方法:
```js
    axios.get(url[, config])
    axios.post(url[, data[, config]])
    axios.delete(url[, config])
    axios.head(url[, config])
    axios.options(url[, config])
    axios.put(url[, data[, config]])
    axios.patch(url[, data[, config]])
```

除了上面的快捷方法，也可以通过配置来进行数据请求:
```js
    this.axios({
        method: 'get',
        url: ...
    }).then((res) => {
        console.log(res.status)
    })
```

多数时候，在同一个项目中，使用的请求很多配置都是相同的。对于这种情况，可以创建一个新的 axios 请求实例，之后所有的请求都使用这个实例来发起，实例本身的配置会与快捷方法的配置合并:
```js
    const instance = this.axios.create({
        baseURL: '/myApi',
        timeout: 1000,
        headers: { 'X-Custom-Header': 'custom' }
    })
    ...
    instance.get(...).then(...)
```

#### 请求的配置与响应数据结构

| 参数 | 意义 | 值 |
|:----|:-----|:---|
| url | 设置请求的接口 URL | 字符串 |
| method | 设置请求方法 | 字符串，默认为'get' |
| baseURL | 设置请求的接口前缀，会拼接在 URL 之前 | 字符串 |
| transformRequest | 用来拦截请求，在发起请求前进行数据的修改 | 函数，此函数会传入 data、headers 两个参数，将修改后的 data 进行返回即可 |
| transformResponse | 用来拦截请求回执，在收到请求回执后调用 | 函数，此函数会传入 data 作为参数，将修改后的 data 进行返回即可 |
| headers | 自定义请求头 | 对象 |
| paramsSerializer | 自定义参数的序列化方法 | 函数 |
| data | 设置请求要发送的数据 | 字符、对象、数组等 |
| timeout | 设置请求的超时时间 | 数值，单位为毫秒，若设置为 0 则永不超时 |
| withCredentials | 设置跨域请求时是否需要凭证 | 布尔值 |
| auth | 设置用户信息 | 对象 |
| responseType | 设置响应数据的数据类型 | 字符串，默认为'json' |
| responseEncoding | 设置响应数据的编码方式 | 字符串，默认为 'utf8' |
| maxContentLength | 设置允许响应的最大字节数 | 数值 |
| maxBodyLength | 设置请求内容的最大字节数 | 数值 |
| validateStatus | 自定义请求结束的状态是成功还是失败 | 函数，会传入请求到的 status 状态码作为参数，需要返回布尔值决定请求是否成功 |

当一个请求被发出后，axios 会返回一个 Promise 对象，通过此 Promise 对象可以异步地等待数据的返回，axios 返回的数据是一个包装好的对象，其中包装的属性列举如下:

| 属性 | 意义 | 值 |
|:----|:-----|:---|
| data | 接口服务返回的响应数据 | 对象 |
| status | 接口服务返回的 HTTP 状态码 | 数值 |
| statusText | 接口服务返回的 HTTP 状态信息 | 字符串 |
| headers | 响应头数据 | 对象 |
| config | axios 设置的请求配置信息 | 对象 |
| request | 请求实例 | 对象 |

#### 拦截器的使用

拦截器的功能在于其允许开发者在请求发起前或请求完成后进行拦截，从而在这些时候添加一些定制化的逻辑。

例如，在请求发送前，可能需要激活页面的 Loading 特效，在请求完成后移除 Loading 特效，同时，如果请求的结果是异常的，可能还需要进行一个弹窗提示，而这些逻辑对于项目中的大部分请求来说都是通用的，这时就可以使用拦截器。

要对请求的开始进行拦截:
```js
    this.axios.interceptors.request.use((config) => {
        alert('请求将要开始')
        return config
    },(error) => {
        alert('请求出现错误')
        return Promise.reject(error)
    })
    this.axios.get(api).then((response) => {
        console.log(response.data)
    })
```

也可以对请求完成后进行拦截:
```js
    this.axios.interceptors.response.use((response) => {
        alert(response.status)
        return response
    },(error) => {
        return Promise.reject(error)
    })
```
在拦截器中，也可以对响应数据进行修改，将修改后的数据返回给请求调用处使用。

需要注意的是，请求拦截器的添加是和 axios 请求实例绑定的，后续此实例发起的请求都会被拦截器拦截，但是可以使用如下方式在不需要拦截器的时候将其移除:
```js
    let i = this.axios.interceptors.request.use((config) => {...})
    this.axios.interceptors.request.eject(i)
```
