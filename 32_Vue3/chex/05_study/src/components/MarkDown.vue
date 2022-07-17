<template>
  <p v-html="data"></p>
</template>>

<script>
import { marked }  from 'marked'

export default {
  // 提供外部属性和设置内容
  props: ['content'],
  computed: {
    data() {
      // 计算属性，将外部设置的文章 markdown 内容转换成 HTML
      return marked(this.content);
    }
  }
}
</script>>