<template>
  <body class="__className_20951f">
    <div class="bg-gray-100 dark:bg-blueish-light flex flex-col min-h-screen">
      <Navbar />
      <div class="max-w-screen-md w-full p-4 mx-auto my-auto">
        <h1
          class="mb-4 text-center text-gray-700 dark:text-white font-bold text-md sm:text-xl lg:text-3xl"
        >
          Changelog
        </h1>
        <ol class="relative border-l border-gray-200 dark:border-gray-700">
          <li class="mb-10 ml-4">
            <div
              class="absolute w-3 h-3 bg-gray-200 rounded-full mt-1.5 -left-1.5 border border-white dark:border-gray-900 dark:bg-gray-700"
            ></div>
            <time class="mb-1 text-sm font-normal leading-none text-gray-400 dark:text-gray-500"
              >July 2023</time
            >
            <h3 class="text-lg font-semibold text-gray-900 dark:text-white">
              30,000 users, 50,000 reports, report editing, industry classification, more
              improvements
            </h3>
            <p class="text-base font-normal text-gray-500 dark:text-gray-400">
              We've reached amazing numbers and we're just getting started!<br /><br />We've added
              the ability to edit reports by exporting them to Google Docs for subscribers, and
              we've added beta industry classification through the NAICS system on the report
              page.<br /><br />We've refactored the entire frontend to use Next.js and updated our
              deployment strategy for a faster, more reliable experience and a better overall feel.
            </p>
          </li>
          <li class="mb-10 ml-4">
            <div
              class="absolute w-3 h-3 bg-gray-200 rounded-full mt-1.5 -left-1.5 border border-white dark:border-gray-900 dark:bg-gray-700"
            ></div>
            <time class="mb-1 text-sm font-normal leading-none text-gray-400 dark:text-gray-500"
              >June 2023</time
            >
            <h3 class="text-lg font-semibold text-gray-900 dark:text-white">
              20,000 users, new experience and major performance improvements
            </h3>
            <p class="mb-4 text-base font-normal text-gray-500 dark:text-gray-400">
              We've completely redesigned the app from the ground up to be faster, more reliable,
              and more beautiful. We've also tweaked small details across the app to make it more
              usable and accessible.
            </p>
          </li>
          <li class="mb-10 ml-4">
            <div
              class="absolute w-3 h-3 bg-gray-200 rounded-full mt-1.5 -left-1.5 border border-white dark:border-gray-900 dark:bg-gray-700"
            ></div>
            <time class="mb-1 text-sm font-normal leading-none text-gray-400 dark:text-gray-500"
              >May 2023</time
            >
            <h3 class="text-lg font-semibold text-gray-900 dark:text-white">Integration updates</h3>
            <p class="text-base font-normal text-gray-500 dark:text-gray-400">
              We've integrated VenturusAI into the
              <a
                class="no-underline text-greenish-light hover:text-greenish-dark dark:text-greenish-light dark:hover:text-white"
                rel="nofollow"
                href="https://www.reddit.com/r/business_ideas/"
                >r/Business_Ideas subreddit</a
              >
              for enhanced user experience. This allows users to receive feedback not only from
              VenturusAI but also from the broader Business_Ideas community.
            </p>
          </li>
          <li class="mb-10 ml-4">
            <div
              class="absolute w-3 h-3 bg-gray-200 rounded-full mt-1.5 -left-1.5 border border-white dark:border-gray-900 dark:bg-gray-700"
            ></div>
            <time class="mb-1 text-sm font-normal leading-none text-gray-400 dark:text-gray-500"
              >April 2023</time
            >
            <h3 class="text-lg font-semibold text-gray-900 dark:text-white">
              10,000 users, advanced reports and new integrations
            </h3>
            <div class="text-base font-normal text-gray-500 dark:text-gray-400">
              Enhance your business ideas with our latest additions:
              <ul>
                <li>- Comprehensive MVP Development</li>
                <li>- Effective Go-to-Market Strategies</li>
                <li>- Distinctive Unique Selling Points</li>
                <li>- Detailed Financial Analysis</li>
              </ul>
              <br />Experimental Discord and API support is also available for subscribers.
            </div>
          </li>
          <li class="mb-4 ml-4">
            <div
              class="absolute w-3 h-3 bg-gray-200 rounded-full mt-1.5 -left-1.5 border border-white dark:border-gray-900 dark:bg-gray-700"
            ></div>
            <time class="mb-1 text-sm font-normal leading-none text-gray-400 dark:text-gray-500"
              >March 2023</time
            >
            <h3 class="text-lg font-semibold text-gray-900 dark:text-white">
              Initial launch, our first 5,000 users, industry mentions
            </h3>
            <p class="text-base font-normal text-gray-500 dark:text-gray-400">
              We've launched our beta to the public and are excited to welcome our first 5,000 users
              who analyzed their business ideas with us.<br />
              We're also thankful for all the feedback we've received so far, and features in the
              industry and social media.<br />
              Together, we're embarking on a journey to make business analysis more accessible to
              everyone!
            </p>
          </li>
        </ol>
      </div>
      <FooterP />
    </div>
  </body>
</template>

<script>
import Navbar from '../myComponents/navbar.vue'
import FooterP from '../myComponents/footer.vue'

export default {
  components: {
    Navbar,
    FooterP
  },
  name: 'Changelog-P',
  mounted() {
    document.title = 'Changelog - VenturusAI'
  }
}
</script>
