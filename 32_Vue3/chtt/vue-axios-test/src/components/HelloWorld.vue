<template>
  <div class="hello">
  </div>
</template>

<script>
export default {
  mounted() {
    let city = '上海'
    city = encodeURI(city)
    let api = `/csp/api/v2.1/weather?openId=aiuicus&clientType=android&sign=android&city=${city}`
    this.axios.get('/myApi' + api).then((response) => {
      console.log(response.data.data.list)
    })
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
