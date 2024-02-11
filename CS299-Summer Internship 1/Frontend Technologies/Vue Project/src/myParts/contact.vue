<template>
  <div class="p-4 max-w-screen-lg mx-auto">
    <h1 class="text-md sm:text-xl lg:text-3xl mt-4 mb-5 text-center text-gray-700 dark:text-white">
      Send us a message, feedback, idea or just say hi!
    </h1>
    <form class="flex flex-col gap-4 w-full justify-center" autocomplete="off">
      <div class="relative">
        <input
          type="text"
          id="floating_outlined"
          class="block px-2.5 pb-2.5 pt-4 w-full text-sm text-gray-900 bg-transparent rounded-lg border-1 border-gray-300 appearance-none dark:text-white dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
          placeholder=" "
        />
        <label
          for="floating_outlined"
          class="absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-4 scale-75 top-2 z-10 origin-[0] bg-white dark:bg-blueish-light px-2 peer-focus:px-2 peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:-translate-y-1/2 peer-placeholder-shown:top-1/2 peer-focus:top-2 peer-focus:scale-75 peer-focus:-translate-y-4 left-1"
          >Floating outlined</label
        >
      </div>
      <button
        type="submit"
        disabled=""
        class="group flex h-min items-center justify-center p-0.5 text-center font-medium focus:z-10 focus:outline-none cursor-not-allowed opacity-50 text-green-900 bg-white border border-greenish-light hover:bg-greenish-lighter hover:text-white focus:ring-greenish-light disabled:hover:bg-white disabled:hover:text-greenish-dark dark:bg-greenish-light dark:text-white dark:border-greenish-light dark:hover:bg-greenish-dark dark:hover:border-greenish-dark dark:disabled:hover:text-white dark:focus:ring-greenish-dark rounded-lg focus:ring-2"
      >
        <span class="flex items-center rounded-md text-sm px-4 py-2">
          <span>
            <svg
              stroke="currentColor"
              fill="currentColor"
              stroke-width="0"
              viewBox="0 0 20 20"
              aria-hidden="true"
              class="mr-1 rotate-90"
              height="1em"
              width="1em"
              xmlns="http://www.w3.org/2000/svg"
            >
              <path
                d="M10.894 2.553a1 1 0 00-1.788 0l-7 14a1 1 0 001.169 1.409l5-1.429A1 1 0 009 15.571V11a1 1 0 112 0v4.571a1 1 0 00.725.962l5 1.428a1 1 0 001.17-1.408l-7-14z"
              ></path>
            </svg>
            Send
          </span>
        </span>
      </button>
    </form>
  </div>
</template>

<script>
export default {
  name: 'contact-1'
}
</script>
