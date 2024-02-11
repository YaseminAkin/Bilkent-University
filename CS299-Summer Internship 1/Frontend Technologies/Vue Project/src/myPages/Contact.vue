<template>
  <body class="__className_20951f">
    <div class="bg-gray-100 dark:bg-blueish-light flex flex-col min-h-screen">
      <Navbar />
      <Contact />
      <FooterP />
    </div>
  </body>
</template>

<script>
import Navbar from '../myComponents/navbar.vue'
import FooterP from '../myComponents/footer.vue'
import Contact from '@/myParts/contact.vue'

export default {
  components: {
    Navbar,
    Contact,
    FooterP
  },
  name: 'Contact-P',
  mounted() {
    document.title = 'Contact - VenturusAI'
  }
}
</script>
