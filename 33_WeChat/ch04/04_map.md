
[参考](https://developers.weixin.qq.com/miniprogram/dev/component/map.html)

通过指定经纬度，即可显示该区域的地图，还可以添加标记点、路线、圆、控件等。

map 组件的常用属性如下:

| 属性 | 类型 | 默认值 | 必填 | 说明 |
|:----|:-----|:-------|:----|:-----|
| longitude | number | | 是 | 中心经度 |
| latitude | number | | 是 | 中心纬度 |
| scale | number | 16 | 否 | 缩放级别，取值范围为 3-20 |
| markers | Array | | 否 | 标记点 |
| polyline | Array | | 否 | 路线 |
| circles | Array | | 否 | 圆 |
| show-location | boolean | false | 否 | 显示带有方向的当前定位点 |
| bindmarkertap | eventhandle | | 否 | 点击标记点时触发，会返回 market 的 id |
| bindregionchange | eventhandle | | 否 | 视野发生变化时触发 |
| bindtap | eventhandle | | 否 | 点击地图时触发 |
| bindupdated | eventhandle | | 否 | 在地图渲染更新完成时触发 |

'markers'、'polyline'、'circles' 的值都是由对象组成的数组。

`marker` 标记点用于在地图上显示标记的位置。其常用属性如下:

| 属性 | 说明 | 类型 | 必填 | 备注 |
|:-----|:----|:-----|:----|:-----|
| id | 标记点id | number | 否 | marker 点击事件回调会返回 id |
| longitude | 经度 | number | 是 | 浮点数，范围 -180~180 |
| latitude | 纬度 | number | 是 | 浮点数，范围 -90~90 |
| title | 标注点名 | string | 否 | 点击时显示，callout 存在时将被忽略 |
| zIndex | 显示层级 | number | 否 | |
| iconPath | 显示的图标 | string | 是 | 项目目录下的图片路径，支持网络路径、本地路径、代码包路径 |
| rotate | 旋转角度 | number | 否 | 顺时针旋转的角度，范围0~360, 默认 0 |
| alpha | 标注的透明度 | number | 否 | 默认 1，无透明，范围 0~1 |
| width | 标注图标宽度 | number/string | 否 | 默认为图片实际宽度 |
| height | 标注图标高度 | number/string | 否 | 默认为图片实际高度 |

> 注: 建议为每个 marker 设置 number 类型 id，保证更新 marker 时有更好的性能。

`polyline` 指定一系列坐标点，从数组第一项连线至最后一项。绘制彩虹线时，需指定不同分段的颜色，如 points 包含 5 个点，则 colorList 应传入 4 个颜色值；若 colorList 长度小于 points.length - 1，则剩下的分段颜色与最后一项保持一致。其常用属性如下:

| 属性 | 说明 | 类型 | 必填 | 备注 |
|:-----|:----|:----|:-----|:-----|
| points | 经纬度数组 | array | 是 | [{latitude:0,longitude:0}] |
| color | 线的颜色 | string | 否 | 十六进制 |
| width | 线的宽度 | number | 否 | |
| dottedLine | 是否虚线 | boolean | 否 | 默认 false |

`circle` 在地图上显示圆。常用属性如下:

| 属性 | 说明 | 类型 | 必填 | 备注 |
|:----|:-----|:-----|:----|:-----|
| latitude | 纬度 | number | 是 | 浮点数，范围 -90~90 |
| longitude | 经度 | number | 是 | 浮点数，范围 -180~180 |
| color | 描边的颜色 | string | 否 | 十六进制 |
| fillColor | 填充颜色 | string | 否 | 十六进制 |
| radius | 半径 | number | 是 | |
| strokeWidth | 描边的宽度 | number | 否 | |

由于 map 组件需要给定经纬度，可以通过[坐标拾取器](https://lbs.qq.com/getPoint/)来获取。

获取经纬度后，在 wxml 文件中编写 map 组件，代码如下:
```xml
  <map latitude="40.060148" longitude="116.343219" scale="18"></map>
```

另外，小程序提供了打开微信内置地图的 API 和定位用户位置的 API，需要用户授权才能使用，也就是会自动提示用户`是否同意获取您的位置 `，同意后即可获取。

使用微信内置地图需要在 `app.json` 文件中添加授权，具体配置如下:
```json
  "permission": {
    "scope.userLocation": {
      "desc": "请点击确定"
    }
  }
```

示例代码:
```xml
  <button bindtap="buttonTap">查看我的位置</button>
```
```js
  buttonTap: function() {
    wx.getLocation({
      type: 'gcj02',
      success: function(res) {
        console.log(res.latitude)
        console.log(res.longitude)
        wx.openLocation({
          latitude: res.latitude,
          longitude: res.longitude
        })
      }
    })
  },
```
`type` 属于用于设置返回的坐标信息，默认值为`wgs84`，表示返回 GPS 坐标，设为 `gcj02` 表示返回用于 `wx.openLocation()` 方法的坐标。

[地图使用示例](t/mapt)
