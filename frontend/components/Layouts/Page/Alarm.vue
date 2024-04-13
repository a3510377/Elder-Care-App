<template>
  <div class="fixed bottom-8 right-8 gap-3 flex flex-col">
    <div
      class="flex items-center justify-center relative w-56 h-20 bg-slate-100 rounded-lg transition-transform -translate-y-5 duration-300"
      v-for="(message, id) in alarmMap.data"
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
      <p>{{ message }}</p>
    </div>
  </div>
</template>

<script lang="ts" setup>
import { User, IDeviceEnvWarn } from '~/type';

const alarmMap = useAlarmMap();

onMounted(() => {
  Object.assign(window, {
    alert_test: (data: string) => alarmMap.data.push(data),
  });

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
          {
            const user = data.user as User;
            alarmMap.data.push(`${user.name} 跌倒了!!`);
          }
          break;
        case 'poll':
          ws.send(JSON.stringify({ event: 'poll' }));
          break;
        case 'warn':
          {
            const user = data.user as User;
            const warnData = data.data as IDeviceEnvWarn;

            const warnMessages: string[] = [];
            const messageMap: Record<string, string> = {
              co: '一氧化炭濃度',
              co2: '二氧化炭濃度',
              pm2_5: '空氣品質',
            };

            for (const [key, _] of Object.entries(warnData)) {
              if (key in messageMap) warnMessages.push(messageMap[key]);
            }
            console.info('get warn data:', warnData);

            alarmMap.data.push(
              `${user.name} ${warnMessages.join('/')} 超標了!!`
            );
          }
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
