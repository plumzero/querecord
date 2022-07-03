<template>
  <h1>HelloWorld</h1>
  <p>
    <router-link to="/user/小王/8888">小王</router-link>
    <br>
    <router-link to="/user/小李/6666">小李</router-link>
  </p>
  <router-view></router-view>
</template>

<script>
export default {
  name: 'App',
  components: {
    UserAbout
  }
}
</script>

