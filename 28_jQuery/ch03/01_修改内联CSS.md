
jQuery 提供了 `.css()` 方法。

`backgroundColor` <=> `background-color`

获取
```js
    // 取得单个属性的值
    .css('property')
    // 返回 'value'

    // 取得多个属性的值
    .css(['property1', 'property-2'])
    // 返回 {"property1": "value1", "property-2": "value2"}
```

设置
```js
    // 单个属性及其值
    .css('property', 'value')

    // 属性-值对构成的对象
    .css({
        property1: 'value1',
        'property-2': 'value2'
    })
```

使用 `.css()` 的方式与前面使用 `.addClass()` 的方式相同————将它连缀到 jQuery 对象后面，这个 jQuery 对象包含一组 DOM 元素。

字号增大:
```js
    $(document).ready(function() {
        var $speech = $('div.speech');  // $speech 中的 $ 本身并无特殊含义，只是提醒程序员 speech 保存的是一个 jQuery 对象
        $('#switcher-large').click(function() {
            var num = parseFloat($speech.css('fontSize'));
            $('div.speech').css('fontSize');
            num *= 1.4;     // 字号增大 40%
            $speech.css('fontSize', num + 'px');
        });
    });
```

字号减小:
```js
    $(document).ready(function() {
        var $speech = $('div.speech');
        $('#switcher button').click(function() {
            var num = parseFloat($speech.css('fontSize'));
            if (this.id == 'switcher-large') {
                num *= 1.4;
            } else if (this.id == 'switcher-small') {
                num /= 1.4;
            }
            $speech.css('fontSize', num + 'px');
        });
    });
```

回到默认字号:
```js
    $(document).ready(function() {
        var $speech = $('div.speech');
        var defaultSize = $speech.css('fontSize');
        $('#switcher button').click(function() {
            var num = parseFloat($speech.css('fontSize'));
            switch(this.id) {
                case 'switcher-large':
                    num *= 1.4;
                    break;
                case 'switcher-small':
                    num /= 1.4;
                    break;
                default:
                    num = parseFloat(defaultSize);
            }
            $speech.css('fontSize', num + 'px');
        });
    });
```

### 带厂商前缀的样式属性

浏览器厂商在引入试验性的样式属性时，通常会在实现达到 CSS 规范要求之前，在属性名前面添加一个前缀。等到实现和规范都稳定之后，这些属性的前缀就会被去掉，让开发人员使用标准的名称。因此，我们经常会在样式表里看到一些类似下面这样的 CSS 声明:
```css
    -webkit-property-name: value;
    -moz-property-name: value;
    -ms-property-name: value;
    -o-property-name: value;
    property-name: value;
```
如果想在 JavaScript 中设置这些属性，需要提前检测它们在 DOM 中是否存在，从 propertName 到 WebkitPropertyName，再到 msPropertyName...都要检测。但在 jQuery 中，我们可以直接使用标准的属性名，比如: `.css('propertyName', 'value')`。如果样式对象中不存在这个属性，jQuery 就会依次检测所有带前缀(Webkit、O、Moz、ms)的属性，然后使用第一个找到的那个属性。
