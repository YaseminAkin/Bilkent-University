<template>
  <footer class="bg-white p-4 py-8 md:p-8 xl:p-10 mt-auto dark:bg-blueish-dark">
    <div class="mx-auto max-w-screen-xl text-center">
      <div class="grid grid-cols-1 justify-items-center lg:justify-items-stretch lg:grid-cols-4">
        <a href="/">
          <img
            alt="logo"
            loading="lazy"
            width="100"
            height="25"
            decoding="async"
            data-nimg="1"
            class="object-cover mt-1 h-9 w-auto dark:hidden"
            style="color: rgba(0, 0, 0, 0)"
            src="https://venturusai.com/logo-light.svg"
          />
          <img
            alt="logo"
            loading="lazy"
            width="100"
            height="25"
            decoding="async"
            data-nimg="1"
            class="object-cover mt-1 h-9 w-auto hidden dark:block"
            style="color: rgba(0, 0, 0, 0)"
            src="https://venturusai.com/logo.svg"
          />
        </a>
        <ul
          class="lg:col-span-3 flex flex-wrap justify-center lg:justify-end items-center align-center mb-4 mt-4 lg:mt-0 text-sm text-gray-500 lg:mb-0 dark:text-gray-400"
        >
          <li><a class="hover:underline mr-4 lg:mr-6" href="/plans">Pricing</a></li>
          <li>
            <a
              href="https://status.venturusai.com/"
              target="_blank"
              rel="noreferrer noopener"
              class="hover:underline mr-4 lg:mr-6"
              >Status</a
            >
          </li>
          <li>
            <a class="hover:underline mr-4 lg:mr-6" href="/terms-of-service"
              >Terms and conditions</a
            >
          </li>
          <li><a class="hover:underline mr-4 lg:mr-6" href="/privacy-policy">Privacy policy</a></li>
          <li>
            <a
              href="https://venturusai-1.getrewardful.com/signup"
              target="_blank"
              rel="noreferrer noopener"
              class="hover:underline mr-4 lg:mr-6"
              >Affiliates</a
            >
          </li>
          <li><a class="hover:underline mr-4 lg:mr-6" href="/changes">Changelog</a></li>
          <li><a class="hover:underline" href="/contact">Contact</a></li>
        </ul>
      </div>
      <hr class="my-6 border-gray-200 sm:mx-auto dark:border-gray-700 xl:my-8" />
      <div class="sm:items-center sm:justify-between sm:flex">
        <span class="block text-sm text-gray-500 dark:text-gray-400">
          © Copyright 2023. All Rights Reserved by
          <a class="text-greenish" href="https://venturusai.com"> VenturusAI, Inc. </a>
        </span>
        <div class="flex justify-center mt-4 space-x-6 sm:mt-0">
          <a
            href="https://linkedin.com/company/venturusai"
            rel="noopener noreferrer"
            target="_blank"
            class="text-gray-500 hover:text-gray-900 dark:hover:text-white dark:text-gray-400"
          >
            <!-- SVG code for LinkedIn -->
          </a>
          <a
            href="https://twitter.com/venturusai"
            rel="noopener noreferrer"
            target="_blank"
            class="text-gray-500 hover:text-gray-900 dark:hover:text-white dark:text-gray-400"
          >
            <!-- SVG code for Twitter -->
          </a>
          <a
            href="mailto:support@venturusai.com"
            rel="noopener noreferrer"
            target="_blank"
            class="text-gray-500 hover:text-gray-900 dark:hover:text-white dark:text-gray-400"
          >
            <!-- SVG code for Email -->
          </a>
        </div>
      </div>
    </div>
  </footer>
</template>

<script>
export default {
  name: 'footer-c'
}
</script>

<style scoped>
/* Your component-specific styles here */
</style>
