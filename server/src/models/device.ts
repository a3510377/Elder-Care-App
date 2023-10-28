import { Model, Schema, model } from 'mongoose';

export const DeviceSchema = new Schema<
  IDevice,
  Model<IDevice, {}, IDeviceMethods>,
  IDeviceMethods
>({});

export const DeviceModel = model('device', DeviceSchema, void 0, {
  overwriteModels: true,
});

export interface IDeviceMethods {}

export type IDevice = IRawDeviceWatch | IRawDeviceEnv;
export type DeviceTypesType = IDevice['type'];
export type DateType = `${string}/${string}/${string}`; // YYYY-MM-DD

export interface IAirQualityData {
  type: '10' | '1.0' | '2.5';
  value: number;
}

export interface IRawDeviceWatch {
  type: 0;

  stepCount?: { [date: DateType]: number[][] }; // every minute
  heartbeat?: { [date: DateType]: number[][] }; // every minute
  temp?: { [date: DateType]: number[][] }; // every minute

  warn: {
    heartbeat?: { date: string; value: number }[];
    temp?: { date: string; value: number }[];
    fall?: string[];
  };
}

export interface IRawDeviceEnv {
  type: 1;

  airQuality?: { [date: DateType]: IAirQualityData[][] }; // every minute
  humidity?: { [date: DateType]: number[][] }; // every minute
  temp?: { [date: DateType]: number[][] }; // every minute

  warn: {
    airQuality?: ({ date: string } & IAirQualityData)[];
    harmfulGas?: { date: string; value: number }[];
  };
}
