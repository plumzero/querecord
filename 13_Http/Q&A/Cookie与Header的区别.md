
## 原生 http Header 览

- http 请求头(request Header)
    <pre>
        <strong>Accept:</strong> text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
        <strong>Accept-Encoding:</strong> gzip, deflate
        <strong>Accept-Language:</strong> zh-CN
        <strong>Cache-Control:</strong> max-age=0
        <strong>Connection:</strong> keep-alive
        <strong>Cookie:</strong> BAIDUID=D41049BDFE74A65692C7F10D53C95782;FG=1;BIDUPSID=9E
        <strong>DNT:</strong> 1
        <strong>Host:</strong> www.baidu.com
        <strong>Upgrade-Insecure-Requests:</strong> 1
        <strong>User-Agent:</strong> Mozilla/5.0 (Windows NT 6.1; WOW64)
    </pre>

- http 响应头(response Header)
  <pre>
    <strong>BDPAGETYPE:</strong> 3
    <strong>BDQID:</strong> 0xad2a1d57000e59f8
    <strong>BDUSERED:</strong> 111115218
    <strong>Cache-Control:</strong> private
    <strong>CKPACKNUM:</strong> 2
    <strong>CKRNDSTR:</strong> 7000e59f8
    <strong>Connection:</strong> keep-alive
    <strong>Content-Encoding:</strong> gzip
    <strong>Content-Type:</strong> text/html;charset=utf-8
    <strong>Data:</strong> Thu, 11 Aug 2020 01:41:49 GMT
    <strong>P3P:</strong> CP=" OTI DSP COR IVA OUR IND COM "
    <strong>Server:</strong> bfe/1.0.8.14
    <strong>Set-Cookie:</strong> BDSVRTM=19; path=/
    <strong>Set-Cookie:</strong> BD_CK_SAM=1;path=/
    <strong>Set-Cookie:</strong> H_PS_PSSID=1457_11882_20012_20770; path=/; domain=.baidu.com
    <strong>Set-Cookie:</strong> __bsi=15631840701055775257_00_29_R_N_21_0303_C02F_N_I_I_0; expires=Thu, 11-Aug-16 01:41:54 GMT; domain=www.baidu.com; path=/
    <strong>Set-Cookie:</strong> BDRCVFR[T6vU1RAZ_Ds]=mk3SLVN4HKm; path=; domain=.baidu.com
    <strong>Strict-Transport-Security:</strong> max-age=604800
    <strong>Transfer-Encoding:</strong> chunked
    <strong>Vary:</strong> Accept-Encoding
    <strong>X-Powered-By:</strong> HPHP
    <strong>X-UA-Compatible:</strong> IE=Edge,chrome=1
  </pre>

## Cookie 与 Header 的区别

- Cookie 只是 Header 的一部分。
- Cookie 一般由服务端生成，将其保存到 Session 中。之后将这个 Cookie 发给客户端，进行后续的会话。
  Header 由发送方添加到请求头中，一般不会对发送者有所限制。
- 因为 Cookie 通常由一方生成，只能用于会话双方的交互，所以 Cookie 不会跨域(比如不能用于分布式系统)。
  Header 可以进行跨域访问，比如 JWT(Json Web Token) 一般就通过 Header 的 `Authorization` 进行发送。
- Cookie 一般存在一个有效期，用于说明这段连接的持续会话时间。
  Header 只进行信息的存储。
- Header 一次只能保存一个键值对，而 Cookie 则不作限制。