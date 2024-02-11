<template>
  <section class="bg-gray-100 dark:bg-blueish-light">
    <div class="max-w-screen-xl px-4 py-8 mx-auto lg:gap-20 lg:py-16">
      <div class="w-full place-self-center lg:col-span-6">
        <div class="p-6 mx-auto bg-white rounded-lg shadow dark:bg-blueish-dark sm:max-w-xl sm:p-8">
          <h1
            class="mb-2 text-2xl font-bold leading-tight tracking-tight text-gray-900 dark:text-white"
          >
            Welcome back
          </h1>
          <p class="text-sm font-light text-gray-500 dark:text-gray-300">
            Login to analyze your business idea in minutes.
          </p>
          <form class="mt-4 space-y-6 sm:mt-6" action="#">
            <div class="space-y-4">
              <a
                class="w-full inline-flex items-center justify-center py-2.5 px-5 mr-2 text-sm font-medium text-gray-900 focus:outline-none bg-white rounded-lg border border-gray-200 hover:bg-gray-100 hover:text-gray-900 focus:z-10 focus:ring-4 focus:ring-gray-200 dark:focus:ring-gray-700 dark:bg-blueish-darker dark:text-gray-400 dark:border-gray-600 dark:hover:text-white dark:hover:bg-blueish-lighter cursor-pointer"
                href="https://accounts.google.com/o/oauth2/auth/oauthchooseaccount?access_type=offline&client_id=659216517822-dgoel7i0mcr5pe5huqe6ncqno0p8bkfg.apps.googleusercontent.com&redirect_uri=https%3A%2F%2Fapi.venturusai.com%2Fomniauth%2Fgoogle_oauth2%2Fcallback&response_type=code&scope=email%20profile&state=25ee07176b13b6315cc839525675f519a098bd0877ff44cf&service=lso&o2v=1&flowName=GeneralOAuthFlow"
                target="_blank"
                rel="noopener noreferrer"
              >
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 512 512"
                  class="w-5 h-5 mr-2"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    d="M457.6 224l-2.1-8.9H262V297h115.6c-12 57-67.7 87-113.2 87-33.1 0-68-13.9-91.1-36.3-23.7-23-38.8-56.9-38.8-91.8 0-34.5 15.5-69 38.1-91.7 22.5-22.6 56.6-35.4 90.5-35.4 38.8 0 66.6 20.6 77 30l58.2-57.9c-17.1-15-64-52.8-137.1-52.8-56.4 0-110.5 21.6-150 61C72.2 147.9 52 204 52 256s19.1 105.4 56.9 144.5c40.4 41.7 97.6 63.5 156.5 63.5 53.6 0 104.4-21 140.6-59.1 35.6-37.5 54-89.4 54-143.8 0-22.9-2.3-36.5-2.4-37.1z"
                  ></path>
                </svg>
                <span>Continue with Google</span>
              </a>
              <a
                class="w-full inline-flex items-center justify-center py-2.5 px-5 mr-2 text-sm font-medium text-gray-900 focus:outline-none bg-white rounded-lg border border-gray-200 hover:bg-gray-100 hover:text-gray-900 focus:z-10 focus:ring-4 focus:ring-gray-200 dark:focus:ring-gray-700 dark:bg-blueish-darker dark:text-gray-400 dark:border-gray-600 dark:hover:text-white dark:hover:bg-blueish-lighter cursor-pointer"
                href="https://www.facebook.com/privacy/consent/gdp/?params%5Bapp_id%5D=1092722495456849&params%5Bdisplay%5D=%22page%22&params%5Berror_unsupported_step%5D=false&params%5Bkid_directed_site%5D=false&params%5Blogger_id%5D=%22aa5b420b-0889-4b22-abac-7cbbd1291368%22&params%5Bnext%5D=%22read%22&params%5Bredirect_uri%5D=%22https%3A%5C%2F%5C%2Fapi.venturusai.com%5C%2Fomniauth%5C%2Ffacebook%5C%2Fcallback%22&params%5Bresponse_type%5D=%22code%22&params%5Breturn_scopes%5D=false&params%5Bscope%5D=%5B%22email%22%5D&params%5Bstate%5D=%22023f9a3ed76b7fec3c555383ed8842bb13da3c15cb3aefa3%22&params%5Bsteps%5D=%7B%22read%22%3A%5B%22email%22%2C%22baseline%22%2C%22public_profile%22%5D%7D&params%5Btp%5D=%22unspecified%22&params%5Bcui_gk%5D=%22login_platformization_read%22&source=gdp_delegated"
                target="_blank"
                rel="noopener noreferrer"
              >
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 512 512"
                  class="w-5 h-5 mr-2"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    d="M426.8 64H85.2C73.5 64 64 73.5 64 85.2v341.6c0 11.7 9.5 21.2 21.2 21.2H256V296h-45.9v-56H256v-41.4c0-49.6 34.4-76.6 78.7-76.6 21.2 0 44 1.6 49.3 2.3v51.8h-35.3c-24.1 0-28.7 11.4-28.7 28.2V240h57.4l-7.5 56H320v152h106.8c11.7 0 21.2-9.5 21.2-21.2V85.2c0-11.7-9.5-21.2-21.2-21.2z"
                  ></path>
                </svg>
                <span>Continue with Facebook</span>
              </a>
              <a
                class="w-full inline-flex items-center justify-center py-2.5 px-5 mr-2 text-sm font-medium text-gray-900 focus:outline-none bg-white rounded-lg border border-gray-200 hover:bg-gray-100 hover:text-gray-900 focus:z-10 focus:ring-4 focus:ring-gray-200 dark:focus:ring-gray-700 dark:bg-blueish-darker dark:text-gray-400 dark:border-gray-600 dark:hover:text-white dark:hover:bg-blueish-lighter cursor-pointer"
                href="https://api.twitter.com/oauth/authenticate?oauth_token=VdOxUQAAAAABksP4AAABifMXq2w"
                target="_blank"
                rel="noopener noreferrer"
              >
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 512 512"
                  class="w-5 h-5 mr-2"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <path
                    d="M492 109.5c-17.4 7.7-36 12.9-55.6 15.3 20-12 35.4-31 42.6-53.6-18.7 11.1-39.4 19.2-61.5 23.5C399.8 75.8 374.6 64 346.8 64c-53.5 0-96.8 43.4-96.8 96.9 0 7.6.8 15 2.5 22.1-80.5-4-151.9-42.6-199.6-101.3-8.3 14.3-13.1 31-13.1 48.7 0 33.6 17.2 63.3 43.2 80.7-16-.4-31-4.8-44-12.1v1.2c0 47 33.4 86.1 77.7 95-8.1 2.2-16.7 3.4-25.5 3.4-6.2 0-12.3-.6-18.2-1.8 12.3 38.5 48.1 66.5 90.5 67.3-33.1 26-74.9 41.5-120.3 41.5-7.8 0-15.5-.5-23.1-1.4C62.8 432 113.7 448 168.3 448 346.6 448 444 300.3 444 172.2c0-4.2-.1-8.4-.3-12.5C462.6 146 479 129 492 109.5z"
                  ></path>
                </svg>
                <span>Continue with Twitter</span>
              </a>
              <a
                class="w-full inline-flex items-center justify-center py-2.5 px-5 mr-2 text-sm font-medium text-gray-900 focus:outline-none bg-white rounded-lg border border-gray-200 hover:bg-gray-100 hover:text-gray-900 focus:z-10 focus:ring-4 focus:ring-gray-200 dark:focus:ring-gray-700 dark:bg-blueish-darker dark:text-gray-400 dark:border-gray-600 dark:hover:text-white dark:hover:bg-blueish-lighter cursor-pointer"
                href="https://www.reddit.com/login/?dest=https%3A%2F%2Fssl.reddit.com%2Fapi%2Fv1%2Fauthorize%3Fclient_id%3DMhgT3lEl2ts1mU4osGY1KA%26redirect_uri%3Dhttps%253A%252F%252Fapi.venturusai.com%252Fomniauth%252Freddit%252Fcallback%26response_type%3Dcode%26scope%3Didentity%26state%3Df25e4b6b7ecb3cac72ac714f43fde4359d9c3b26dfe2c139"
                target="_blank"
                rel="noopener noreferrer"
              >
                <svg
                  stroke="currentColor"
                  fill="currentColor"
                  stroke-width="0"
                  viewBox="0 0 512 512"
                  class="w-5 h-5 mr-2"
                  height="1em"
                  width="1em"
                  xmlns="http://www.w3.org/2000/svg"
                >
                  <circle cx="322.3" cy="288.4" r="31.8"></circle>
                  <circle cx="190.3" cy="288.4" r="31.8"></circle>
                  <path
                    d="M480.5 251c0-27.7-22.2-50.2-49.5-50.2-13 0-24.7 5-33.6 13.3-33.2-23.4-78.4-38.5-128.7-40.7L292 95.7l69.6 13.9c.2 24.7 20.1 44.7 44.5 44.7 24.6 0 44.5-20.2 44.5-45.1S430.7 64 406.1 64c-18.6 0-34.5 11.6-41.2 28l-85.2-17-29.4 98.2-7.1.2c-50.3 2.2-95.5 17.4-128.7 40.7-8.8-8.3-20.6-13.3-33.6-13.3-27.3 0-49.5 22.5-49.5 50.2 0 19.6 11 36.5 27.1 44.8-.8 4.9-1.2 9.8-1.2 14.8C57.5 386.4 146.4 448 256 448s198.5-61.6 198.5-137.5c0-5-.4-9.9-1.1-14.8 16.1-8.3 27.1-25.2 27.1-44.7zM406.1 81.9c14.8 0 26.8 12.2 26.8 27.2s-12 27.2-26.8 27.2-26.8-12.2-26.8-27.2 12-27.2 26.8-27.2zM49.2 251c0-17.8 14.3-32.2 31.8-32.2 7.2 0 13.9 2.5 19.2 6.6-17.3 15.2-30.1 33-37 52.4-8.4-5.9-14-15.7-14-26.8zm337.2 141.9C351.8 416.8 305.5 430 256 430s-95.8-13.2-130.4-37.1c-32.5-22.5-50.4-51.8-50.4-82.4 0-3.2.2-6.5.6-9.7.7-6 2.2-11.9 4.3-17.7 5.6-15.6 16-30.3 30.7-43.4 4.4-3.9 9.2-7.7 14.4-11.3.1-.1.3-.2.4-.3C160.2 204.2 206.5 191 256 191s95.8 13.2 130.4 37.1c.1.1.3.2.4.3 5.2 3.6 10 7.4 14.4 11.3 14.7 13.1 25.1 27.8 30.7 43.4 2.1 5.8 3.5 11.7 4.3 17.7.4 3.2.6 6.4.6 9.7 0 30.6-17.9 59.9-50.4 82.4zm62.4-115.2c-6.9-19.4-19.7-37.2-37-52.4 5.3-4.1 12-6.6 19.2-6.6 17.5 0 31.8 14.5 31.8 32.2 0 11.2-5.6 21-14 26.8z"
                  ></path>
                  <path
                    d="M320.5 357.9c-.2.2-24.2 24.2-64.5 24.4-40.9-.2-64.4-24.2-64.6-24.4l-12.6 12.4c1.2 1.2 29.6 29.5 77.2 29.7 47.6-.2 75.9-28.5 77.1-29.7l-12.6-12.4z"
                  ></path>
                </svg>
                <span>Continue with Reddit</span>
              </a>
            </div>
          </form>
        </div>
      </div>
    </div>
  </section>
</template>

<script>
export default {
  name: 'login-1'
}
</script>
