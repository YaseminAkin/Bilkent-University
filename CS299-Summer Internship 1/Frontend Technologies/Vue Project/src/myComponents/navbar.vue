<template>
  <header>
    <nav class="bg-white border-gray-200 px-4 lg:px-6 py-2.5 lg:py-5 dark:bg-blueish-dark rounded">
      <div class="flex flex-wrap justify-between items-center mx-auto max-w-screen-xl">
        <div class="flex items-center">
          <a href="/">
            <img
              alt="logo"
              loading="lazy"
              width="100"
              height="25"
              decoding="async"
              data-nimg="1"
              class="object-cover mt-1 h-9 w-auto dark:hidden"
              style="color: transparent"
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
              style="color: transparent"
              src="https://venturusai.com/logo.svg"
            />
          </a>
        </div>
        <div class="flex items-center md:order-2">
          <a
            class="text-primary-600 dark:text-primary-500 ml-1 lg:ml-3 hover:bg-gray-50 focus:ring-4 focus:ring-gray-300 font-medium rounded-lg text-sm px-3 lg:px-5 py-2 lg:py-2.5 dark:hover:bg-gray-700 focus:outline-none dark:focus:ring-gray-800"
            href="/login"
          >
            Login/Register
          </a>
          <button
            data-testid="flowbite-navbar-toggle"
            class="inline-flex items-center rounded-lg p-2 text-sm text-gray-500 hover:bg-gray-100 focus:outline-none focus:ring-2 focus:ring-gray-200 dark:text-gray-400 dark:hover:bg-gray-700 dark:focus:ring-gray-600 md:hidden"
          >
            <span class="sr-only">Open main menu</span>
            <svg
              stroke="currentColor"
              fill="currentColor"
              stroke-width="0"
              viewBox="0 0 448 512"
              aria-hidden="true"
              class="h-6 w-6 shrink-0"
              height="1em"
              width="1em"
              xmlns="http://www.w3.org/2000/svg"
            >
              <path
                d="M16 132h416c8.837 0 16-7.163 16-16V76c0-8.837-7.163-16-16-16H16C7.163 60 0 67.163 0 76v40c0 8.837 7.163 16 16 16zm0 160h416c8.837 0 16-7.163 16-16v-40c0-8.837-7.163-16-16-16H16c-8.837 0-16 7.163-16 16v40c0 8.837 7.163 16 16 16zm0 160h416c8.837 0 16-7.163 16-16v-40c0-8.837-7.163-16-16-16H16c-8.837 0-16 7.163-16 16v40c0 8.837 7.163 16 16 16z"
              ></path>
            </svg>
          </button>
        </div>
        <div
          data-testid="flowbite-navbar-collapse"
          class="w-full justify-between items-center md:flex md:w-auto md:order-1 hidden mr-10"
        >
          <ul class="mt-4 flex flex-col md:mt-0 md:flex-row md:space-x-8 md:text-sm md:font-medium">
            <li>
              <a
                class="block py-2 pr-4 pl-3 md:p-0 border-b border-gray-100 text-gray-700 hover:bg-gray-50 dark:border-gray-700 dark:text-gray-400 dark:hover:bg-gray-700 dark:hover:text-white md:border-0 md:hover:bg-transparent md:hover:text-greenish-light md:dark:hover:bg-transparent md:dark:hover:text-white"
                href="/example-reports"
              >
                Report Examples
              </a>
            </li>
            <li>
              <a
                class="block py-2 pr-4 pl-3 md:p-0 border-b border-gray-100 text-gray-700 hover:bg-gray-50 dark:border-gray-700 dark:text-gray-400 dark:hover:bg-gray-700 dark:hover:text-white md:border-0 md:hover:bg-transparent md:hover:text-greenish-light md:dark:hover:bg-transparent md:dark:hover:text-white"
                href="/plans"
              >
                Pricing
              </a>
            </li>
            <li>
              <a
                class="block py-2 pr-4 pl-3 md:p-0 border-b border-gray-100 text-gray-700 hover:bg-gray-50 dark:border-gray-700 dark:text-gray-400 dark:hover:bg-gray-700 dark:hover:text-white md:border-0 md:hover:bg-transparent md:hover:text-greenish-light md:dark:hover:bg-transparent md:dark:hover:text-white"
                href="/contact"
              >
                Contact
              </a>
            </li>
          </ul>
        </div>
      </div>
    </nav>
  </header>
</template>

<script>
export default {
  name: 'navbar-c'
}
</script>

<style scoped>
/* Your component-specific styles here */
</style>
