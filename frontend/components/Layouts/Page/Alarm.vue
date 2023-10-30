<template>
  <div class="fixed bottom-8 right-8 gap-3 flex flex-col">
    <div
      class="flex items-center justify-center relative w-56 h-20 bg-slate-100 rounded-lg transition-transform -translate-y-5 duration-300"
      v-for="(user, id) in alarmMap.data"
      :key="id"
    >
      <span class="-top-1 -left-1 absolute flex h-3 w-3">
        <span
          class="animate-ping absolute inline-flex h-full w-full rounded-full bg-red-400 opacity-75"
        ></span>
        <span
          class="relative inline-flex rounded-full h-3 w-3 bg-red-500"
        ></span>
      </span>
      <div
        class="top-2 right-2 absolute rounded-full p-0.5 cursor-pointer hover:bg-slate-300"
        @click="() => alarmMap.data.splice(id, 1)"
      >
        <Icon name="mdi:close" class="!block" width="18px" height="18px" />
      </div>
      <p>{{ user.name }} 跌倒了!!</p>
    </div>
  </div>
</template>

<script lang="ts" setup>
import { User } from '~/type';

const alarmMap = useAlarmMap();

onMounted(() => {
  const {
    public: { apiUrl },
  } = useRuntimeConfig();

  let loop: NodeJS.Timeout;
  const connect = () => {
    clearTimeout(loop);

    const ws = new WebSocket(apiUrl.replace(/http(s)?:\/\/(.*)/, 'ws$1://$2'));
    ws.addEventListener('message', ({ data: rawData }) => {
      const { data, event } = JSON.parse(rawData);

      switch (event) {
        case 'fall':
          alarmMap.data.push(data.user as User);
          break;
        case 'poll':
          ws.send(JSON.stringify({ event: 'poll' }));
          break;
      }
    });

    const reconnect = () => (loop = setTimeout(connect, 1e3));
    ws.addEventListener('close', reconnect);
    ws.addEventListener('error', reconnect);
  };
  connect();
});
</script>

<style lang="scss" scoped></style>
