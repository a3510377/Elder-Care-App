import { reactive } from 'vue';
import { User } from '../type';

export const useAlarmMap = () => reactive<User[]>([]);
