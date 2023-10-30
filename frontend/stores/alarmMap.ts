import { User } from '../type';

export const useAlarmMap = defineStore('AlarmMap', {
  state: (): { data: User[] } => ({ data: [] }),
});
