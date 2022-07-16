<template>
  <HelloWorld1></HelloWorld1>
  <HelloWorld2></HelloWorld2>
</template>

<script>
import HelloWorld1 from './components/HelloWorld.vue'
import HelloWorld2 from './components/HelloWorld2.vue'

export default {
  name: 'App',
  components: {
    HelloWorld1,
    HelloWorld2
  }
}
</script>

<style>
</style>
