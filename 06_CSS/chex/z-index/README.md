

- `z-index` 可以设置元素的叠加顺序，但依赖定位属性，即只作用于带有定位属性的元素。如果 `position` 属性为 `static` 的时候，就相当于没有定位属性。
- `z-index` 大的元素会覆盖 `z-index` 小的元素。
- `z-index` 为 `auto` 的元素不参与层级比较。
- `z-index` 为负值，元素被普通流中的元素覆盖。


### 01

z-index 与 `position: relative` 和 `float` 一起使用。

- [测试html](01.html)
- [测试css](01.css)
