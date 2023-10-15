<template>
  <div
    :to="`/devices/${deviceBody?.id}`"
    class="bg-gray-800 border-2 border-slate-600 hover:bg-[#25303f] p-3 rounded"
  >
    <div class="flex mb-3">
      <span class="block bg-cyan-400 w-3 mr-1.5"></span>
      <span>手錶 [{{ deviceBody?.id }}]</span>
    </div>
    <div>
      <div>
        <div>
          <p>心跳:</p>
          <Line
            :data="{
              labels: Array.from({ length: 24 }).map((_, i) => i),
              datasets: [{ backgroundColor: '#f87979', data: heartbeat }],
            }"
            :options="{ borderColor: '#f87979' }"
          />
        </div>
        <div>
          <p>皮膚溫度:</p>
          <Line
            :data="{
              labels: Array.from({ length: 24 }).map((_, i) => i),
              datasets: [{ backgroundColor: '#f87979', data: temperature }],
            }"
            :options="{ borderColor: '#f87979' }"
          />
        </div>
        <div>
          <p>步數:</p>
          <Line
            :data="{
              labels: Array.from({ length: 24 }).map((_, i) => i),
              datasets: [{ backgroundColor: '#f87979', data: stepCount }],
            }"
            :options="{ borderColor: '#f87979' }"
          />
        </div>
      </div>
    </div>
  </div>
</template>

<script lang="ts" setup>
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
} from 'chart.js';

import { Line } from 'vue-chartjs';

import { APIRequestBody, IDeviceWatch } from '~/type';

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

const { data: deviceData } = await useFetch<APIRequestBody<IDeviceWatch>>(
  `${apiUrl}/api/devices/${deviceId}`
);
const deviceBody = computed(() => deviceData.value?.body);

const getDate = (): `${string}/${string}/${string}` => {
  const now = new Date();

  return `${now.getFullYear()}/${now.getMonth() + 1}/${now.getDate()}`;
};

const heartbeat = computed(() => {
  return (
    deviceBody.value?.heartbeat?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b)
    ) || []
  );
});
const temperature = computed(() => {
  return (
    deviceBody.value?.temp?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b)
    ) || []
  );
});
const stepCount = computed(() => {
  const data =
    deviceBody.value?.stepCount?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b)
    ) || [];

  let last = 0;
  const newData: number[] = [];
  for (const d of data) {
    newData.push(d - last);
    last = d || 0;
  }

  return newData;
});
</script>

<style lang="scss" scoped></style>
