<template>
  <div class="fixed bottom-8 right-8 gap-3 flex flex-col">
    <div
      class="relative w-56 h-20 bg-slate-100 rounded-lg transition-transform -translate-y-5 duration-300"
      v-for="_ in 2"
    >
      <div
        class="top-2 right-2 absolute rounded-full p-0.5 cursor-pointer hover:bg-slate-300"
        @click="() => console.log('awa')"
      >
        <Icon name="mdi:close" class="!block" width="18px" height="18px" />
      </div>
    </div>
  </div>
</template>

<script lang="ts" setup></script>

<style lang="scss" scoped></style>
