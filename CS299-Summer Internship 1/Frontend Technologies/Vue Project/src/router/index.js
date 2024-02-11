import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../myPages/Home.vue'
import ReportExamples from '@/myPages/ReportExamples.vue'
import Pricing from '@/myPages/Pricing.vue'
import Contact from '@/myPages/Contact.vue'
import Login from '@/myPages/Login.vue'
import Changelog from '@/myPages/Changelog.vue'
import PrivacyPolicy from '@/myPages/PrivacyPolicy.vue'
import TermsandConditions from '@/myPages/TermsandConditions.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView
    },
    {
      path: '/example-reports',
      name: 'reportexapmles',
      component: ReportExamples
    },
    {
      path: '/plans',
      name: 'pricing',
      component: Pricing
    },
    {
      path: '/contact',
      name: 'contact',
      component: Contact
    },
    {
      path: '/login',
      name: 'login',
      component: Login
    },
    {
      path: '/changes',
      name: 'changelog',
      component: Changelog
    },
    {
      path: '/privacy-policy',
      name: 'privacypolicy',
      component: PrivacyPolicy
    },
    {
      path: '/terms-of-service',
      name: 'terms',
      component: TermsandConditions
    }
  ]
})

export default router
