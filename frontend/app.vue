<template>
  <Body class="bg-gray-900">
    <NuxtLayout>
      <NuxtPage />
    </NuxtLayout>
  </Body>
</template>

<script lang="ts" setup>
useHead({
  meta: [
    {
      'http-equiv': 'Content-Security-Policy',
      content: 'upgrade-insecure-requests',
    },
  ],
});
</script>
