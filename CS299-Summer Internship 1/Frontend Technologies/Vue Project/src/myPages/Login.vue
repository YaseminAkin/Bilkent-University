<template>
  <body class="__className_20951f">
    <div class="bg-gray-100 dark:bg-blueish-light flex flex-col min-h-screen">
      <Navbar />
      <Login />
      <FooterP />
    </div>
  </body>
</template>

<script>
import Navbar from '../myComponents/navbar.vue'
import FooterP from '../myComponents/footer.vue'
import Login from '@/myParts/login.vue'

export default {
  components: {
    Navbar,
    Login,
    FooterP
  },
  name: 'Login-P',
  mounted() {
    document.title = 'Login - VenturusAI'
  }
}
</script>
