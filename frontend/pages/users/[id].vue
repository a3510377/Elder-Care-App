<template>
  <GeneralHead />
  <div class="flex items-start justify-center w-full py-5">
    <div
      class="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 xl:grid-cols-5 gap-5 p-4 text-gray-50"
    >
      <PageDevice
        v-for="(device, i) in userBody?.devices"
        :key="i"
        :device-id="device"
      />
    </div>
  </div>
</template>

<script lang="ts" setup>
import { APIRequestBody, User } from '~/type';

const route = useRoute();

const {
  public: { apiUrl },
} = useRuntimeConfig();

const { data: userData } = await useFetch<APIRequestBody<User>>(
  `${apiUrl}/api/users/${route.params.id}`,
  { server: false }
);
const userBody = computed(() => userData.value?.body);
</script>

<style lang="scss" scoped></style>
