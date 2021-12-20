
Date 类型将日期保存为自协调世界时(UTC)时间 1970 年 1 月 1 日午夜(零时)至今所经过的毫秒数。

创建一个保存当前日期和时间的 Date 对象:
```js
    let now = new Date();
```

`Date.parse()` 方法接收一个表示日期的字符串参数，尝试将这个字符串转换为表示该日期的毫秒数。

创建一个表示 "2021 年 12 月 18 日"的日期对象:
```js
    let someDate = new Date(Date.parse("Dec 18, 2021"));
```
也可以简写为:
```js
    let someDate = new Date("Dec 18, 2021");
```

`Date.now()` 返回执行时日期和时间的毫秒数。
```js
    let start = Date.now();
```

### 继承的方法

Date 类型重写了 `toLocaleString()`、`toString()` 和 `valueOf()` 方法。
- `toLocaleString()` 方法返回与浏览器运行的本地环境一致的日期和时间
- `toString()` 方法通常返回带时区信息的日期和时间

### 日期格式化

- `toDateString()` 显示日期中的周几、月、日、年
- `toTimeString()` 显示日期中的时、分、秒和时区
- `toLocaleDateString()` 显示日期中的周几、月、日、年
- `toLocaleTimeString()` 显示日期中的时、分、秒
- `toUTCString()` 显示完整的 UTC 日期

### 日期/时间组件方法

部分常用...

| 方法  | 说明  |
|:------|:------|
| getTime() | 返回日期的毫秒表示 |
| setTime(milliseconds) | 设置日期的毫秒表示，从而修改整个日期 |
| getFullYear() | 返回 4 位数年(即 2021 而不是 21) |
| getMonth() | 返回日期的月(0 表示 1 月, 11 表示 12 月) |
| getDate() | 返回日期中的日(1~31) |
| getDay() | 返回日期中表示周几的数值(0表示周日，6表示周六) |
| getHours() | 返回日期中的时(0~23) |
| getMinutes() | 返回日期中的分(0~59) |
| getSeconds() | 返回日期中的秒(0~59) |
| getMilliseconds() | 返回日期中的毫秒 |
