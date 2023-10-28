<template>
  <GeneralHead page-title="用戶" />
  <div class="flex items-start justify-center w-full py-5">
    <div
      class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-5 p-4 text-gray-50"
    >
      <PageUser v-for="(user, i) in data?.body" :key="i" :user="user" />
    </div>
  </div>
</template>

<script lang="ts" setup>
import { APIRequestBody, User } from '~/type';

const {
  public: { apiUrl },
} = useRuntimeConfig();

const { data: data } = await useFetch<APIRequestBody<User[]>>(
  `${apiUrl}/api/users`,
  { server: false }
);
</script>
