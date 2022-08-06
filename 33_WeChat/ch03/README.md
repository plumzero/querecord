
本节以实现一个'音乐'小程序项目来说明各组件的使用。

该小程序页面结构由上、中、下 3 个区域组成，分别命名为 tab、content 和 player。

tab 区域用于显示标签页标题，在 content 区域内通过左右滑动可以实现标签页的切换，底部的 player 区域用于显示当前播放的音乐信息。

本项目的目录结构如下:

| 路径 | 说明 |
|:-----|:----|
| app.js | 应用程序的逻辑文件 |
| app.json | 应用程序的配置文件 |
| pages/index/index.js | index 页面的逻辑文件 |
| pages/index/index.json | index 页面的配置文件 |
| pages/index/index.wxss | index 页面的样式文件 |
| pages/index/index.wxml | index 页面的结构文件 |
| pages/index/info.wxml | '音乐推荐'标签页的结构文件 |
| pages/index/play.wxml | '播放器'标签页的结构文件 |
| pages/index/playlist.wxml | '播放列表' 标签页的结构文件 |
| images | 图片文件 |

该项目实际上只有一个页面，wxml 结构被拆分成了 4 个文件，分别是 index.wxml、info.wxml、play.wxml 和 playlist.wxml，整体的页面结构代码在 index.wxml 中编写。