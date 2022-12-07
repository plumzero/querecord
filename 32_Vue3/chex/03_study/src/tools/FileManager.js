
import axios from 'axios'

const FileManager = {
    path: process.env.BASE_URL + 'post/',  // 项目 public 文件夹下的 post 文件夹路径
    // 获取所有的主题栏目，后续增加可以继续配置
    getAllTopic: function() {
        return [
            'HTML专题',
            'CSS专题'
        ]
    },
    // 获取某个主题下的所有文章，后续增加可以继续配置
    getPosts: function(topic) {
        switch(Number(topic)) {
            case 0:
                return ['表单简介', '常用表单']
            case 1:
                return ['选择器', '盒子模型']
        }
    },
    // 获取某个文章的详细内容
    getPostContent: function(topicName, postName) {
        let url = this.path + topicName + '/' + postName + '.md'
        return new Promise((res, rej) => {
            axios.get(url).then((response) => {
                console.log(response.data)
                res(response)
            }, rej)
        })
    }
}

export default FileManager
