<template>
  <h1>HelloWorld</h1>
  <p>
    <router-link to="/user/小王">小王</router-link>
    <br>
    <router-link to="/user/6666">小李</router-link>
    <br>
    <router-link to="/category/一级/二级/三级">分类</router-link>
    <br>
    <router-link to="/user/">无用户</router-link>
    <br>
    <router-link to="/user/小红/friends/6">二级路由</router-link>
  </p>
  <router-view></router-view>
</template>

<script>
export default {
  name: 'App',
  components: {
  }
}
</script>

