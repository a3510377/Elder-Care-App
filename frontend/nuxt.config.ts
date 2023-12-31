// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  devtools: { enabled: true },
  modules: ['@nuxtjs/tailwindcss', '@vueuse/nuxt', 'nuxt-icon', '@pinia/nuxt'],
  runtimeConfig: {
    public: {
      apiUrl: 'http://127.0.0.1:8000',
    },
  },
  components: [
    {
      prefix: 'Layout',
      path: '~/components/Layouts',
      global: true,
    },
    {
      prefix: 'Page',
      path: '~/components/Pages',
      global: true,
    },
    { path: '~/components/utils', global: true },
  ],
  imports: {
    dirs: [
      // Scan top-level modules
      'stores',
    ],
  },
});
