<template>
  <div class="flex space-x-4">
    <LayoutPageNavbarMenuItem v-for="(item, i) in menu" :key="i" :menu="item" />
  </div>
</template>

<script lang="ts" setup>
import { MenuItem } from '~/type';

const { menu } = defineProps<{ menu: MenuItem[] }>();
</script>

<style lang="scss" scoped></style>
