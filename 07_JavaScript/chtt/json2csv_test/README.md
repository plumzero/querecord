
```js
    npm install json2csv
```

测试版本 5.0.7 。


### 记录

```js
    import { Parser } from 'json2csv';
```
像上面这样导入会报如下错误:
```sh
    SyntaxError: The requested module 'json2csv' is expected to be of type CommonJS, which does not support named exports. CommonJS modules can be imported by importing the default export.
```

应该像上面这样导入:
```js
    import json2csv from 'json2csv';

    const { Parser } = json2csv;
```
