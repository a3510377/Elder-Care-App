<template>
  <div class="flex mb-3">
    <span class="block bg-cyan-400 w-3 mr-1.5"></span>
    <span class="text-ellipsis overflow-hidden"> 手錶 [{{ device?.id }}] </span>
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
</template>

<script lang="ts" setup>
import { Line } from 'vue-chartjs';

import { IDeviceWatch } from '~/type';

const { device } = defineProps<{ device: IDeviceWatch }>();
const deviceBody = computed(() => device.data);

const getDate = (): `${string}/${string}/${string}` => {
  const now = new Date();

  return `${now.getFullYear()}/${now.getMonth() + 1}/${now.getDate()}`;
};

const heartbeat = computed(() => {
  return (
    deviceBody.value?.heartbeat?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b, 0)
    ) || []
  );
});
const temperature = computed(() => {
  return (
    deviceBody.value?.temp?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b, 0)
    ) || []
  );
});
const stepCount = computed(() => {
  const data =
    deviceBody.value?.stepCount?.[getDate()]?.map((d) =>
      d?.filter(Boolean).reduce((a, b) => a + b, 0)
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
