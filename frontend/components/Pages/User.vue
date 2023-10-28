<template>
  <NuxtLink
    :to="`/users/${user.id}`"
    class="bg-gray-800 border-2 border-slate-600 hover:bg-[#25303f] p-3 rounded"
  >
    <div class="flex mb-3">
      <span class="block bg-cyan-400 w-3 mr-1.5"></span>
      <span class="text-ellipsis overflow-hidden">
        {{ user.name }} [{{ user.id }}]
      </span>
    </div>
    <div>
      <div>
        <div>
          <p>地址:</p>
          <div class="text-sm">{{ user.address }}</div>
        </div>
        <div>
          <p>設備:</p>
          <div class="text-sm">
            <p
              class="text-ellipsis overflow-hidden"
              v-for="id in user.device"
              :key="id"
            >
              {{ id }}
            </p>
          </div>
        </div>
      </div>
    </div>
  </NuxtLink>
</template>

<script lang="ts" setup>
import { User } from '~/type';

const { user } = defineProps<{ user: User }>();
</script>

<style lang="scss" scoped></style>
