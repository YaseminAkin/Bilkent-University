<template>
  <body class="__className_20951f">
    <div class="bg-gray-100 dark:bg-blueish-light flex flex-col min-h-screen">
      <Navbar />
      <Pricing />
      <FooterP />
    </div>
  </body>
</template>

<script>
import Navbar from '../myComponents/navbar.vue'
import FooterP from '../myComponents/footer.vue'
import Pricing from '../myParts/pricing.vue'

export default {
  components: {
    Navbar,
    Pricing,
    FooterP
  },
  name: 'Pricing-P',
  mounted() {
    document.title = 'Pricing - VenturusAI'
  }
}
</script>
