import { IAlarm } from '~/type';

export const useAlarmMap = defineStore('AlarmMap', {
  state: (): { data: IAlarm[] } => ({ data: [] }),
});
