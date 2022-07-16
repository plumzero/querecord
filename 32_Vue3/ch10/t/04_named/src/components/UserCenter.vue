
<template>
    <h1>用户中心</h1>
    <h2>姓名: {{$route.params.username}}</h2>
</template>

<script>
export default {
    // mounted() {
    //     alert(`页面加载时执行一次，请求数据。路由参数为 name:${this.$route.params.username} id:${this.$route.params.id}`)
    // }
};
</script>