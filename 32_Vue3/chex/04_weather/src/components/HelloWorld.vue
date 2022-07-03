<template>
  <el-container class="container">
    <el-header>
      <el-input placeholder="请输入" class="input" v-model="city">
        <template #prepend>城市名:</template>
      </el-input>
    </el-header>
    <el-main class="main">
      <div class="today">
        今天:
        <span>{{this.todayData.weather ?? this.plc}}{{this.todayData.temp ?? this.plc}}</span>
        <span style="margin-left:20px">{{this.todayData.wind ?? this.plc}}</span>
        <span style="margin-left:100px">{{this.todayData.date}}</span>
      </div>
      <div class="real">
        <span class="temp">{{this.realtime.temp ?? this.plc}}°</span>
        <span class="realInfo">{{this.realtime.weather ?? this.plc}}</span>
        <span class="realInfo" style="margin-left:20px">{{this.realtime.wind ?? this.plc}}</span>
        <span class="realInfo" style="margin-left:20px">{{this.realtime.windLevel ?? this.plc}}</span>
      </div>
      <div class="real">
        <span class="realInfo">空气质量:{{this.realtime.airQuality ?? this.plc}}°</span>
        <span class="realInfo" style="margin-left:20px">湿度:{{this.realtime.humidity ?? this.plc}}</span>
      </div>
      <div class="future">
        <div class="header">4日天气预报</div>
        <el-table :data="futureData" style='margin-top:30px'>
          <el-table-column prop="date" label="日期"></el-table-column>
          <el-table-column prop="temp" label="温度"></el-table-column>
          <el-table-column prop="weather" label="天气"></el-table-column>
          <el-table-column prop="wind" label="风向"></el-table-column>
        </el-table>
      </div>
    </el-main>
  </el-container>
</template>

<script>
export default {
  mounted() {
    // 组件挂载时，进行默认数据的初始化
    this.requestData()
  },
  data() {
    return {
      city: '上海',
      weatherData: {},
      todayData: {},
      plc: '暂无数据',
      realtime: {},
      futureData: []
    }
  },
  watch: {
    // 当用户输入的城市发生变化后，调用接口进行数据请求
    city() {
      this.requestData()
    }
  },
  methods: {
    requestData() {
      let city = encodeURI(this.city)
      let api = `/csp/api/v2.1/weather?openId=aiuicus&clientType=android&sign=android&city=${city}`
      this.axios.get('/myApi' + api).then((response) => {
        console.log(response.data.data.list)
        this.weatherData = response.data.data.list
        this.todayData = this.weatherData[0]
        this.realtime = this.todayData
        this.futureData = this.weatherData
      })
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.container {
  background: linear-gradient(rgb(13,104,188), rgb(54,131,195));
}
.input {
  width: 300px;
  margin-top: 20px;
}
.today {
  font-size: 20px;
  color: white;
}
.temp {
  font-size: 79px;
  color: white;
}
.realInfo {
  margin-top: 40px;
}
.header {
  color: white;
  font-size: 27px;
}
</style>
