<template>
  <el-container style="height:100%">
    <el-aside width="200px" style="background-color:#f1f1f1">
      <div></div>
      <el-menu
        mode="vertical"
        background-color="#f1f1f1"
        text-color="#777777"
        active-text-color="#000000"
        default-active="0"
      >
        <el-menu-item
          v-for="item in items"
          :index="item.index+''"
          :key="item.index"
        >
          <div id="text">{{item.title}}</div>
        </el-menu-item>
      </el-menu>
    </el-aside>
    <el-main>
    </el-main>
  </el-container>
</template>

<script>
export default {
  props: ["items"],
  components: {
  }
};
</script>

<style scoped>
.el-menu-item.is-active {
  background-color: #ffffff !important;
}
</style>
