
<template>
  <el-container id="container">
    <el-header style="width:100%" height="120px">
      <Header :items="navItems" v-on:selected="changeSelected"></Header>
    </el-header>
    <el-main>
      <Body :items="bodyItems" :topic="navItems[currentTopicIndex].title"></Body>
    </el-main>
    <el-footer>
      <div id="footer">{{desc}}</div>
    </el-footer>
  </el-container>
</template>

<script>
import SkeletonHeader from './SkeletonHeader.vue'
import SkeletonBody from './SkeletonBody.vue'
import FM from '../tools/FileManager.js'

export default {
  mouted() {
    FM.getPostContent('HTML专题', '表单简介').then((res) => {
      console.log(res)
    })
  },
  components: {
    Header: SkeletonHeader,
    Body: SkeletonBody,
  },
  data() {
    return {
      navItems: FM.getAllTopic().map((item, index) => {
        return {
          index: index,
          title: item
        }
      }),
      desc: '版权所有，仅限学习使用，禁止传播!',
      currentTopicIndex: 0
    }
  },
  methods: {
    changeSelected(index) {
      this.currentTopicIndex = index
    }
  },
  computed: {
    bodyItems() {
      return FM.getPosts(this.currentTopicIndex).map((item,index) => {
        return {
          index: index,
          title: item
        }
      })
    }
  }
}
</script>>

<style scoped>
#container {
  margin-left: 150px;
  margin-right: 150px;
  margin-top: 30px;
  height: 800px;
}
#footer {
  text-align: center;
  background-color: bisque;
  height: 40px;
  line-height: 40px;
  color: #717171;
}
</style>
