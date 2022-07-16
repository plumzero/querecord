<template>
  <h1>Hello World</h1>
  <el-container>
    <p>
      <el-button type="primary" @click="triggerRouter">触发路由</el-button>
    </p>
    <el-header height="80px">
      <router-view name="topBar"></router-view>
    </el-header>
    <el-main>
      <router-view name="main"></router-view>
    </el-main>
  </el-container>
</template>

<script>
export default {
  name: 'App',
  components: {
  },
  methods: {
    triggerRouter() {
      this.$router.push({
        path: '/user/小王/6666'
      })
    }
  }
}
</script>

<style>
</style>
