<template>
  <h1>示例页面1</h1>
  <el-button type="primary" @click="click">跳转Demo2</el-button>
</template>
<script>
import DemoTwo from './DemoTwo.vue';
export default {
  created() {
    console.log(this)
    this.$router.addRoute({
      path: '/demo2',
      component: DemoTwo,
    })
  },
  methods: {
    click() {
      this.$router.push('/demo2');
    }
  }
}
</script>