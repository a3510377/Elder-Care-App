<template>
  <div
    :to="`/devices/${deviceInfo?.id}`"
    class="bg-gray-800 border-2 border-slate-600 hover:bg-[#25303f] p-3 rounded"
  >
    <PageDeviceWatch v-if="deviceInfo?.type === 0" :device="deviceInfo" />
    <PageDeviceEnv v-else-if="deviceInfo?.type === 1" :device="deviceInfo" />
    <slot />
  </div>
</template>

<script lang="ts" setup>
import type { APIRequestBody, Device } from '~/type';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip
);

const { deviceId } = defineProps<{ deviceId: string }>();
const {
  public: { apiUrl },
} = useRuntimeConfig();

const { data: deviceData } = await useFetch<APIRequestBody<Device>>(
  `${apiUrl}/api/devices/${deviceId}`
);
const deviceInfo = computed(() => deviceData.value?.body);
</script>
