<template>
  <h1>计数器2: {{this.$store.state.HelloWorld2.count2}}</h1>
  <button @click="increment">增加</button>
</template>

<script>
export default {
  methods: {
    increment() {
      this.$store.commit({
        type: 'HelloWorld2/increment2',
        count: 2
      })
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
