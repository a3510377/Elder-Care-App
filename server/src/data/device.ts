import { readJsonFile, writeJsonFile } from '@/utils/file';
import { DEVICES_DATA_PATH, init, nextLastDeviceID } from '.';

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

  stepCount?: { [date: DateType]: number[] }; // every minute
  heartbeat?: { [date: DateType]: number[] }; // every minute
  temp?: { [date: DateType]: number[] }; // every minute

  warn: {
    heartbeat?: { date: Date; value: number }[];
    temp?: { date: Date; value: number }[];
    fall?: Date[];
  };
}

export interface IFileDeviceEnv {
  type: 1;

  airQuality?: { [date: DateType]: IAirQualityData[] }; // every minute
  humidity?: { [date: DateType]: number[] }; // every minute
  temp?: { [date: DateType]: number[] }; // every minute

  warn: {
    airQuality?: ({ date: Date } & IAirQualityData)[];
    harmfulGas?: { date: Date; value: number }[];
  };
}

export const readDeviceFile = () => {
  init();

  return readJsonFile<IFileDevices>(DEVICES_DATA_PATH);
};

export const createDevice = (type: DeviceTypes) => {
  const data = readDeviceFile();
  const id = nextLastDeviceID();

  data[id] = { type, warn: {} };

  writeJsonFile(DEVICES_DATA_PATH, data);

  return { ...data[id], id };
};

export const getDeviceFromID = (id: string): IDevice | undefined => {
  const device = readDeviceFile()[id];

  return device ? { id, ...device } : void 0;
};
