import { readJsonFile, writeJsonFile } from '@/utils/file';
import { DEVICES_DATA_PATH, USERS_DATA_PATH, init, nextLastDeviceID } from '.';
import { readUserFile } from './user';

export type IFileDevices = { [device_id: string]: IFileDevice };

export type IFileDevice = IFileDeviceWatch | IFileDeviceEnv;

export type DeviceTypes = IFileDevice['type'];

export type DateType = `${string}/${string}/${string}`; // YYYY-MM-DD

export type IDevice =
  | (IFileDevice & { id: string })
  | (IFileDevice & { id: string });

export interface IAirQualityData {
  type: '10' | '1.0' | '2.5';
  value: number;
}

export interface IFileDeviceWatch {
  type: 0;

  user_id: string;
  stepCount?: { [date: DateType]: number[] }; // every minute
  heartbeat?: { [date: DateType]: number[] }; // every minute
  temp?: { [date: DateType]: number[] }; // every minute

  warn: {
    heartbeat?: { date: string; value: number }[];
    temp?: { date: string; value: number }[];
    fall?: string[];
  };
}

export interface IFileDeviceEnv {
  type: 1;

  user_id: string;
  airQuality?: { [date: DateType]: IAirQualityData[] }; // every minute
  humidity?: { [date: DateType]: number[] }; // every minute
  temp?: { [date: DateType]: number[] }; // every minute

  warn: {
    airQuality?: ({ date: string } & IAirQualityData)[];
    harmfulGas?: { date: string; value: number }[];
  };
}

export const readDeviceFile = () => {
  init();

  return readJsonFile<IFileDevices>(DEVICES_DATA_PATH);
};

export const createDevice = (type: DeviceTypes, user_id: string) => {
  const users = readUserFile();
  const data = readDeviceFile();
  const id = nextLastDeviceID();
  const user = users[user_id];

  if (!user) {
    throw new Error(`User ${user_id} does not exist`);
  }

  data[id] = { type, user_id, warn: {} };
  user.devices.push(id);

  writeJsonFile(USERS_DATA_PATH, user);
  writeJsonFile(DEVICES_DATA_PATH, data);

  return { ...data[id], id };
};

export const getDeviceFromID = (id: string): IDevice | undefined => {
  const device = readDeviceFile()[id];

  return device ? { id, ...device } : void 0;
};

export const writeDeviceFromID = (id: string, data: IDevice) => {
  const rawData = readDeviceFile();

  rawData[id] = data;

  writeJsonFile(DEVICES_DATA_PATH, rawData);
};
