<template>
  <h1>HelloWorld</h1>
  <p>
    <!-- router-link 是路由跳转组件，用 to 来指定要跳转的路由 -->
    <router-link to="/demo1">页面一</router-link>
    <br>
    <router-link to="/demo2">页面二</router-link>
  </p>
  <!-- router-view 是路由的页面出口，路由匹配到的组件会渲染在此 -->
  <router-view></router-view>
</template>

<script>
export default {
  name: 'App',
  components: {
  }
}
</script>
