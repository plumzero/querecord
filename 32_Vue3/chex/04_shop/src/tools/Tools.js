
const Tools = {
    // 导出文件
    exportJson(name, data) {
        var blob = new Blob([data]);
        var link = document.createElement('a')
        link.href = URL.createObjectURL(blob)   // 创建一个 URL 对象并传给 a 元素的 href
        link.download = name    // 设置下载的默认文件名
        link.click()
    }
}

export default Tools
