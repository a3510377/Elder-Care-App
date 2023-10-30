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
    <div
      class="flex"
      :class="{ 'justify-around items-center': user.avatar_hash }"
    >
      <div>
        <div class="text-sm">性別: {{ user.gender ? '女' : '男' }}</div>
        <div class="text-sm">年齡: {{ user.age }}</div>
        <div class="text-sm">備註: {{ user.remark }}</div>
        <div class="text-sm">地址: {{ user.address }}</div>
        <div class="text-sm">電話: {{ user.phone }}</div>
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
      <div v-if="user.avatar_hash">
        <img
          ref="imgRef"
          :src="`${apiUrl}/api/users/${user.id}/avatar`"
          class="rounded max-h-[80px] max-w-[80px]"
          alt="user avatar"
        />
      </div>
    </div>
  </NuxtLink>
</template>

<script lang="ts" setup>
import { User } from '~/type';

const { user } = defineProps<{ user: User }>();
const {
  public: { apiUrl },
} = useRuntimeConfig();
</script>
