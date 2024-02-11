<template>
  <div class="container px-4 py-8 mx-auto lg:px-0">
    <h1
      class="text-center mb-4 text-4xl font-extrabold leading-none tracking-tight text-gray-900 md:text-5xl lg:text-6xl dark:text-white"
    >
      Subscription pricing plans
    </h1>
    <p
      class="text-center mb-6 text-lg font-normal text-gray-500 lg:text-xl sm:px-16 xl:px-48 dark:text-gray-400"
    >
      Unlock insights and opportunities with our range of comprehensive options.
    </p>
    <section
      class="grid grid-cols-1 pt-9 space-y-12 lg:space-y-0 lg:grid-cols-3 lg:gap-x-6 xl-gap-8"
    >
      <div class="flex flex-col p-6 bg-white rounded-lg shadow xl:p-8 dark:bg-blueish-dark">
        <div class="flex-1">
          <h3 class="mb-4 text-2xl font-semibold text-gray-500 dark:text-gray-400">Starter</h3>
          <div class="flex items-baseline mb-4 text-gray-900 dark:text-white">
            <span class="text-5xl font-extrabold tracking-tight dark:text-white">Free</span>
          </div>
          <p class="text-md font-normal text-gray-500 dark:text-gray-400">
            Gain access to Standard reports, perfect for new businesses seeking foundational
            guidance.
          </p>
          <ul class="my-6 space-y-4">
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                10 Standard reports/month
              </span>
              <div data-tooltip-target="tooltip-right" data-tooltip-placement="right">
                <svg
                  stroke="currentColor"
                  fill="none"
                  stroke-width="2"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                  class="text-greenish-light hover:text-greenish-dark cursor-pointer"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                  ></path>
                </svg>
              </div>
              <div
                id="tooltip-right"
                tabindex="-1"
                class="absolute z-10 invisible inline-block px-3 py-2 text-sm font-medium text-white bg-gray-900 rounded-lg shadow-sm opacity-0 tooltip dark:bg-gray-700"
                role="tooltip"
              >
                SWOT, PESTEL, Porter's Five Forces, CATWOE, and many others
                <div class="tooltip-arrow" data-popper-arrow>&nbsp;</div>
              </div>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                0 Advanced reports/month
              </span>
              <div data-tooltip-target="tooltip-right" data-tooltip-placement="right">
                <svg
                  stroke="currentColor"
                  fill="none"
                  stroke-width="2"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                  class="text-greenish-light hover:text-greenish-dark cursor-pointer"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                  ></path>
                </svg>
              </div>
              <div
                id="tooltip-right"
                tabindex="-1"
                class="absolute z-10 invisible inline-block px-3 py-2 text-sm font-medium text-white bg-gray-900 rounded-lg shadow-sm opacity-0 tooltip dark:bg-gray-700"
                role="tooltip"
              >
                Includes Standard report + MVP, Unique Selling Proposition, Go-to-Market strategy,
                and Financial Analysis
                <div class="tooltip-arrow" data-popper-arrow>&nbsp;</div>
              </div>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Idea up to 1000 characters long
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Public/Private reports
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                PDF with watermark</span
              >
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Choose your preferred language
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Own commercial report rights
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Advanced Analysis PAYG: $10
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Early access to major new features
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Support team available
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Access to Discord channel
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Deploy the VenturusAI bot for your community on Discord or Reddit
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                API access
              </span>
            </li>
          </ul>
        </div>
        <a
          class="text-white bg-primary-700 hover:bg-primary-800 focus:ring-4 focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:bg-greenish-light dark:hover:bg-greenish-dark dark:focus:ring-primary-800"
          href="/login"
        >
          Login/Register
        </a>
      </div>
      <div class="flex flex-col p-6 bg-white rounded-lg shadow xl:p-8 dark:bg-blueish-dark">
        <div class="flex-1">
          <h3 class="mb-4 text-2xl font-semibold text-gray-500 dark:text-gray-400">Pro</h3>
          <div class="flex items-baseline mb-4 text-gray-900 dark:text-white">
            <span class="text-3xl font-semibold dark:text-white">$</span>
            <span class="text-5xl font-extrabold tracking-tight dark:text-white">20</span>
            <span class="ml-1 text-2xl font-normal text-gray-500 dark:text-gray-400">/month</span>
          </div>
          <p class="text-md font-normal text-gray-500 dark:text-gray-400">
            Enjoy Standard reports, plus Advanced analysis for a deeper understanding of your
            opportunities.
          </p>
          <ul class="my-6 space-y-4">
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                40 Standard reports/month
              </span>
              <div data-tooltip-target="tooltip-right" data-tooltip-placement="right">
                <svg
                  stroke="currentColor"
                  fill="none"
                  stroke-width="2"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                  class="text-greenish-light hover:text-greenish-dark cursor-pointer"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                  ></path>
                </svg>
              </div>
              <div
                id="tooltip-right"
                tabindex="-1"
                class="absolute z-10 invisible inline-block px-3 py-2 text-sm font-medium text-white bg-gray-900 rounded-lg shadow-sm opacity-0 tooltip dark:bg-gray-700"
                role="tooltip"
              >
                SWOT, PESTEL, Porter's Five Forces, CATWOE, and many others
                <div class="tooltip-arrow" data-popper-arrow>&nbsp;</div>
              </div>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                5 Advanced reports/month
              </span>
              <div data-tooltip-target="tooltip-left" data-tooltip-placement="left">
                <svg
                  stroke="currentColor"
                  fill="none"
                  stroke-width="2"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                  class="text-greenish-light hover:text-greenish-dark cursor-pointer"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                  ></path>
                </svg>
              </div>
              <div
                id="tooltip-left"
                tabindex="-1"
                class="absolute z-10 invisible inline-block px-3 py-2 text-sm font-medium text-white bg-gray-900 rounded-lg shadow-sm opacity-0 tooltip dark:bg-gray-700"
                role="tooltip"
              >
                Includes Standard report + MVP, Unique Selling Proposition, Go-to-Market strategy,
                and Financial Analysis
                <div class="tooltip-arrow" data-popper-arrow>&nbsp;</div>
              </div>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Idea up to 3000 characters long
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Public/Private reports
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                PDF with watermark</span
              >
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Choose your preferred language
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Own commercial report rights
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Advanced Analysis PAYG: $5
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Early access to major new features
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Support team available
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Access to Discord channel (upcoming)
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Deploy the VenturusAI bot for your community on Discord or Reddit
              </span>
            </li>
            <li class="flex space-x-3 text-gray-400 dark:text-gray-500 line-through">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                API access
              </span>
            </li>
          </ul>
        </div>
        <a
          class="text-white bg-primary-700 hover:bg-primary-800 focus:ring-4 focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:bg-greenish-light dark:hover:bg-greenish-dark dark:focus:ring-primary-800"
          href="/login"
        >
          Login/Register
        </a>
      </div>
      <div class="flex flex-col p-6 bg-white rounded-lg shadow xl:p-8 dark:bg-blueish-dark">
        <div class="flex-1">
          <h3 class="mb-4 text-2xl font-semibold text-gray-500 dark:text-gray-400">Agency</h3>
          <div class="flex items-baseline mb-4 text-gray-900 dark:text-white">
            <span class="text-5xl font-extrabold tracking-tight dark:text-white">Contact us</span>
          </div>
          <p class="text-md font-normal text-gray-500 dark:text-gray-400">
            Experience the full suite of features, including integrations and API access for
            seamless use.
          </p>
          <ul class="my-6 space-y-4">
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                300+ Standard reports/month
              </span>
              <div data-tooltip-target="tooltip-right" data-tooltip-placement="right">
                <svg
                  stroke="currentColor"
                  fill="none"
                  stroke-width="2"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                  class="text-greenish-light hover:text-greenish-dark cursor-pointer"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                  ></path>
                </svg>
              </div>
              <div
                id="tooltip-right"
                tabindex="-1"
                class="absolute z-10 invisible inline-block px-3 py-2 text-sm font-medium text-white bg-gray-900 rounded-lg shadow-sm opacity-0 tooltip dark:bg-gray-700"
                role="tooltip"
              >
                SWOT, PESTEL, Porter's Five Forces, CATWOE, and many others
                <div class="tooltip-arrow" data-popper-arrow>&nbsp;</div>
              </div>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                100+ Advanced reports/month
              </span>
              <div data-tooltip-target="tooltip-left" data-tooltip-placement="left">
                <svg
                  stroke="currentColor"
                  fill="none"
                  stroke-width="2"
                  viewBox="0 0 24 24"
                  aria-hidden="true"
                  class="text-greenish-light hover:text-greenish-dark cursor-pointer"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M8.228 9c.549-1.165 2.03-2 3.772-2 2.21 0 4 1.343 4 3 0 1.4-1.278 2.575-3.006 2.907-.542.104-.994.54-.994 1.093m0 3h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                  ></path>
                </svg>
              </div>
              <div
                id="tooltip-left"
                tabindex="-1"
                class="absolute z-10 invisible inline-block px-3 py-2 text-sm font-medium text-white bg-gray-900 rounded-lg shadow-sm opacity-0 tooltip dark:bg-gray-700"
                role="tooltip"
              >
                Includes Standard report + MVP, Unique Selling Proposition, Go-to-Market strategy,
                and Financial Analysis
                <div class="tooltip-arrow" data-popper-arrow>&nbsp;</div>
              </div>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Idea up to 4000 characters long
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Public/Private reports
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                PDF with watermark</span
              >
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Choose your preferred language
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Own commercial report rights
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Lower Advanced Analysis PAYG
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Early access to major new features
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Support team available
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Access to Discord channel (upcoming)
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                Deploy the VenturusAI bot for your community on Discord or Reddit
              </span>
            </li>
            <li class="flex space-x-3 text-greenish-light">
              <svg
                stroke="currentColor"
                fill="none"
                stroke-width="2"
                viewBox="0 0 24 24"
                aria-hidden="true"
                class="flex-shrink-0 w-6 h-6"
                height="1em"
                width="1em"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"></path>
              </svg>
              <span class="text-base font-normal text-gray-500 dark:text-gray-400">
                API access
              </span>
            </li>
          </ul>
        </div>
        <a
          class="text-white bg-primary-700 hover:bg-primary-800 focus:ring-4 focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:bg-greenish-light dark:hover:bg-greenish-dark dark:focus:ring-primary-800"
          href="/login"
        >
          Login/Register
        </a>
      </div>
    </section>

    <section class="mt-8">
      <div class="py-8 px-4 mx-auto max-w-screen-xl sm:py-16 lg:px-6">
        <h2 class="mb-8 text-4xl tracking-tight font-extrabold text-gray-900 dark:text-white">
          Frequently asked questions
        </h2>
        <div
          class="grid pt-8 text-left border-t border-gray-200 md:gap-16 dark:border-gray-700 md:grid-cols-2"
        >
          <div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                What is the difference between One time payments and Subscriptions?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                One time payments allow users to purchase Advanced reports without having to own a
                subscription. One time payments do not include the benefits of having a
                subscription, such as longer prompts (3000-4000 characters compared to 1000 for
                non-subscribers), PDF without watermark, and other features that are exclusive to
                our subscribers. Also, subscribers get a special price when purchasing additional
                reports.
              </p>
            </div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                How do I purchase an advanced report without owning a subscription?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                Once you have created an account, navigate to the top right corner, click on your
                avatar, go to
                <a
                  class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                  href="/settings"
                  >the "Settings" section</a
                >
                and scroll down to the "PAYG (Pay as you go) Advanced reports" section that will
                allow you to purchase advanced reports.
              </p>
            </div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                How do I subscribe to a paid plan?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                To subscribe to a paid plan, you first need to register for an account on our
                platform. After registration, navigate to
                <a
                  class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                  href="/plans"
                  >the pricing page</a
                >, where you'll see the different plans available. At the bottom of each plan,
                you'll find an option to subscribe. Simply click on that option and follow the
                subsequent steps to complete your subscription.
              </p>
            </div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                How do I purchase additional reports as a paid subscriber?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                The process is the same as for non subscribers, just that the price has been
                automatically adjusted to match your paid subscription.
              </p>
            </div>
          </div>
          <div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                How do I cancel my paid subscription?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                To unsubscribe from a paid plan, follow these steps: Click on your profile image in
                the top right corner of the page. Navigate to
                <a
                  class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                  href="/settings"
                  >the "Settings" section</a
                >. Locate the "Subscriptions" area and click on "Manage subscription". You'll be
                redirected to Stripe's page, where you can cancel your subscription.
              </p>
            </div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                What does the free version include?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                The free version includes 10 standard reports per month, allowing you to download
                each report as PDF or to share it. In addition to that you can generate the report
                in your preferred language. You can use this version for any purposes, because you
                own the commercial report rights.
              </p>
            </div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                How do I get access to support as a paid customer?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                If you have any question or you encounter any issue please email
                <a
                  class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                  href="mailto:support@venturusai.com"
                  >support@venturusai.com</a
                >
                from the same email address that you are using on VenturusAI.com. In addition to
                that, you could just use the contact form
                <a
                  class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                  href="/contact"
                  >available here</a
                >.
              </p>
            </div>
            <div class="mb-10">
              <h3 class="flex items-center mb-4 text-lg font-medium text-gray-900 dark:text-white">
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 20 20"
                  aria-hidden="true"
                  class="flex-shrink-0 mr-2 w-5 h-5 text-gray-500 dark:text-gray-400"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    fill-rule="evenodd"
                    d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-8-3a1 1 0 00-.867.5 1 1 0 11-1.731-1A3 3 0 0113 8a3.001 3.001 0 01-2 2.83V11a1 1 0 11-2 0v-1a1 1 0 011-1 1 1 0 100-2zm0 8a1 1 0 100-2 1 1 0 000 2z"
                    clip-rule="evenodd"
                  ></path>
                </svg>
                How do I remove my account from VenturusAI.com?
              </h3>
              <p class="text-gray-500 dark:text-gray-400">
                To get your account removed, please send an email to
                <a
                  class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                  href="mailto:support@venturusai.com"
                  >support@venturusai.com</a
                >
                from the same email address that you are using on VenturusAI.com, requesting to get
                your account removed. Please have in mind that once your account has been removed,
                all your data is permanently deleted and cannot be recovered.
              </p>
            </div>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>

<script>
export default {
  name: 'pricing-1'
}
</script>
