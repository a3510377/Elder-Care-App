<template>
  <header class="flex fixed w-full h-[64px] dark:bg-gray-950">
    <div class="flex flex-1 items-center justify-between px-4">
      <div>
        <NuxtLink
          to="/"
          class="font-bold text-lg text-lime-500 hover:text-lime-600 transition-colors ease-linear"
        >
          Elder-Care-App
        </NuxtLink>
      </div>
      <div>
        <LayoutPageNavbarMenu :menu="menu" />
      </div>
    </div>
  </header>
</template>

<script lang="ts" setup>
import { MenuItem } from '~/type';

const menu: MenuItem[] = [{ type: 'link', title: 'awa', to: '/' }];
</script>

<style lang="scss" scoped>
header {
  display: flex;
}
</style>
