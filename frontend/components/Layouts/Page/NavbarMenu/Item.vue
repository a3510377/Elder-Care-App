<template>
  <template v-if="menu.type === 'link'">
    <NuxtLink :to="menu.to" #="{ isActive }">
      <span
        class="transition-colors ease-linear"
        :class="{
          'text-gray-700 dark:text-gray-400 hover:text-gray-300': !isActive,
          'text-gray-900 dark:text-gray-200 hover:text-gray-100 font-bold':
            isActive,
        }"
      >
        {{ menu.title }}
      </span>
    </NuxtLink>
  </template>
  <template v-else-if="menu.type === 'button'"></template>
  <template v-else-if="menu.type === 'dropdown'"></template>
</template>

<script lang="ts" setup>
import { MenuItem } from '~/type';

const { menu } = defineProps<{ menu: MenuItem }>();
</script>

<style lang="scss" scoped></style>
