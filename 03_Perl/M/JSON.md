
### 源与版本

[JSON-2.90](https://metacpan.org/release/JSON)

[参考](https://metacpan.org/pod/JSON)


### 选择 JSON 模块的 backend

JSON::XS 相对来说应该是更好用的，毕竟 JSON 模块默认使用的是 JSON::XS 。

如果 JSON::XS 不可用，这个时候 JSON 模块 backend 会回退(fall back)到 JSON::PP，如果 JSON::PP 也不可用，JSON 模块 backend 会回退到 JSON::backportPP 。

使用下面的脚本在目标机器上测试一下吧，如果执行正常就说明当前 perl 支持 JSON 模块的 backend:
```pl
    #!/usr/bin/env perl -w

    BEGIN { $ENV{PERL_JSON_BACKEND}='JSON::XS'; }
    use JSON;
```

JSON::XS 并不兼容较高版本的的 perl (version 5.22)。

这里会以 JSON::PP 作为示范。


### 功能接口

> encode_json

默认的编码方式是 utf-8 二进制串编码。
```pl
    $json_text = encode_json($perl_scalar);
```

[示例程序](json/encode.pl)

> decode_json

期望一个 utf-8 二进制串，将其解码为 utf-8 编码的文本。
```pl
    $perl_scalar = decode_json($json_text);
```

[示例程序](json/decode.pl)

> to_json

将给定数据结构转为串，效果和 encode_json 差不多。
```pl
    $json_text = to_json($perl_scalar[, $optional_hashref])
```

[示例程序](json/to_json.pl)

> from_json

将串转为指定数据结构，效果和 decode_json 差不多。
```pl
    $perl_scalar = from_json($json_text[, $optional_hashref])
```

[示例程序](json/from_json.pl)

> JSON::is_bool

判断 scalar 真假。
```pl
    $is_boolean = JSON::is_bool($scalar);
```


### 通用面向对象接口

> new

创建一个 JSON::XS-compatible 对象，用于编/解码字符串。

```pl
    $json = JSON->new();
```

[示例程序](json/object_new.pl)

> property

获取属性标志。
```pl
    $settings = $json->property();
```

每种属性一般都有设置/获得两种方法。

设置为 utf-8 编码:
```pl 
    $json = $json->utf8($enable);
```

是否为 utf-8 编码:
```pl
    $enabled = $json->get_utf8();
```

[示例程序](json/object_attribute.pl)

[类对象的json化](json/object_json.pl)

[复杂结构的json序列化](json/object_serilize.pl)

[复杂结构的json结构化](json/object_structure.pl)