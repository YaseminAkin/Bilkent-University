<template>
  <body class="__className_20951f">
    <div class="bg-gray-100 dark:bg-blueish-light flex flex-col min-h-screen">
      <Navbar />
      <Home1 />
      <Home2 />
      <Home3 />
      <FooterP />
    </div>
  </body>
</template>

<script>
import Home1 from '../myParts/home1.vue'
import Home2 from '../myParts/home2.vue'
import Home3 from '../myParts/home3.vue'
import Navbar from '../myComponents/navbar.vue'
import FooterP from '../myComponents/footer.vue'

export default {
  components: {
    Home1,
    Home2,
    Home3,
    Navbar,
    FooterP
  },
  name: 'Home-P',
  mounted() {
    document.title = 'VenturusAI - Instant feedback on your business ideas'
  }
}
</script>
