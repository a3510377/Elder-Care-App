<template>
  <div class="flex mb-3">
    <span class="block bg-cyan-400 w-3 mr-1.5"></span>
    <span class="text-ellipsis overflow-hidden">
      環境設備 [{{ device?.id }}]
    </span>
  </div>
  <div>
    <div>
      <div>
        <p>一氧化碳:</p>
        <Line
          :data="{
            labels: Array.from({ length: 24 }).map((_, i) => i),
            datasets: [{ backgroundColor: '#f87979', data: co }],
          }"
          :options="{ borderColor: '#f87979' }"
        />
      </div>
      <div>
        <p>二氧化碳:</p>
        <Line
          :data="{
            labels: Array.from({ length: 24 }).map((_, i) => i),
            datasets: [{ backgroundColor: '#f87979', data: co2 }],
          }"
          :options="{ borderColor: '#f87979' }"
        />
      </div>
      <div>
        <p>PM2.5:</p>
        <Line
          :data="{
            labels: Array.from({ length: 24 }).map((_, i) => i),
            datasets: [{ backgroundColor: '#f87979', data: pm2_5 }],
          }"
          :options="{ borderColor: '#f87979' }"
        />
      </div>
    </div>
  </div>
</template>

<script lang="ts" setup>
import { Line } from 'vue-chartjs';

import { IDeviceEnv } from '~/type';

const { device } = defineProps<{ device: IDeviceEnv }>();
const deviceBody = computed(() => device.data);

const getDate = (): `${string}/${string}/${string}` => {
  const now = new Date();

  return `${now.getFullYear()}/${now.getMonth() + 1}/${now.getDate()}`;
};

const co = computed(() => {
  return (
    deviceBody.value?.co?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b, 0)
    ) || []
  );
});
const co2 = computed(() => {
  return (
    deviceBody.value?.co2?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b, 0)
    ) || []
  );
});
const pm2_5 = computed(() => {
  return (
    deviceBody.value?.pm2_5?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b, 0)
    ) || []
  );
});
</script>
