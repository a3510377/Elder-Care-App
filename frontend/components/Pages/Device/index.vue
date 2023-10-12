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
              datasets: [
                {
                  backgroundColor: '#f87979',
                  data:
                    heartbeat?.map((d) =>
                      d?.filter(Boolean).reduce((a, b) => a + b)
                    ) || [],
                },
              ],
            }"
            :options="{
              borderColor: '#f87979',
            }"
          />
        </div>
        <div>
          <p>皮膚溫度:</p>
          <div class="text-sm">
            <Line
              :data="{
                labels: Array.from({ length: 24 }).map((_, i) => i),
                datasets: [
                  {
                    backgroundColor: '#f87979',
                    data:
                      temperature?.map((d) =>
                        d?.filter(Boolean).reduce((a, b) => a + b)
                      ) || [],
                  },
                ],
              }"
              :options="{
                borderColor: '#f87979',
              }"
            />
          </div>
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

const heartbeat = computed(() => deviceBody.value?.heartbeat?.[getDate()]);
const temperature = computed(() => deviceBody.value?.temp?.[getDate()]);
</script>

<style lang="scss" scoped></style>
