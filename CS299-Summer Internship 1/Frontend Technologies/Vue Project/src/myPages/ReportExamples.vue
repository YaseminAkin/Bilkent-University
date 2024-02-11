<template>
  <body class="__className_20951f">
    <div class="bg-gray-100 dark:bg-blueish-light flex flex-col min-h-screen">
      <Navbar />
      <ReportExamples />
      <FooterP />
    </div>
  </body>
</template>

<script>
import Navbar from '../myComponents/navbar.vue'
import FooterP from '../myComponents/footer.vue'
import ReportExamples from '../myParts/reportexamples.vue'

export default {
  components: {
    Navbar,
    ReportExamples,
    FooterP
  },
  name: 'ReportExamples-P',
  mounted() {
    document.title = 'Example reports - VenturusAI'
  }
}
</script>
