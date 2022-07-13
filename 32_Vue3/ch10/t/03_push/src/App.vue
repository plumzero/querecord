<template>
  <h1>Hello World</h1>
  <p>
    <el-button type="primary" @click="toUserFixed">用户中心(固定)</el-button>
  </p>
  <p>
    <el-button type="primary" @click="toUserPass">用户中心(传入)</el-button>
  </p>
  <p>
    <el-button type="primary" @click="toUserQuery">用户中心(带参)</el-button>
  </p>
  <router-view></router-view>
</template>

<script>
export default {
  name: 'App',
  components: {
  },
  methods: {
    toUserFixed() {
      this.$router.push({
        path: '/user/小王'
      })
    },
    toUserPass() {
      this.$router.push({
        name: 'user',
        params: {
          username: '小明'
        }
      })
    },
    toUserQuery() {
      this.$router.push({
        name: 'userx',
        params: {
          username: '小弹'
        },
        query: {
          name: 'xiaotan'
        }
      })
    }
  }
}
</script>

<style>
</style>
