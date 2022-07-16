<template>
  <h1>计数器1: {{this.$store.state.HelloWorld1.count1}}</h1>
  <button @click="increment">增加</button>
</template>

<script>
export default {
  methods: {
    increment() {
      this.$store.commit({
        type: 'HelloWorld1/increment1',
        count: 3
      })
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
