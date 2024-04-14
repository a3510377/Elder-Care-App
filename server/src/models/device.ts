import { Model, Schema, model } from 'mongoose';

export const DeviceSchema = new Schema<
  IDevice,
  Model<IDevice, {}, IDeviceMethods>,
  IDeviceMethods
>({
  type: { type: Number, required: true },
  data: Object,
  warn: Object,
});

DeviceSchema.method('getPublicInfo', function (): IPublicDevice {
  return {
    id: this.id,
    type: this.type,
    data: this.data,
    warn: this.warn,
  } as IPublicDevice;
});

export const DeviceModel = model('device', DeviceSchema, void 0, {
  overwriteModels: true,
});

export interface IDeviceMethods {
  getPublicInfo(): IPublicDevice;
}

export type IDevice = IRawDeviceWatch | IRawDeviceEnv;
export type IPublicDevice = (IRawDeviceWatch | IRawDeviceEnv) & { id: string };
export type DeviceTypesType = IDevice['type'];
export type DateType = `${string}/${string}/${string}`; // YYYY-MM-DD

export interface IAirQualityData {
  type: '10' | '1.0' | '2.5';
  value: number;
}

export interface IRawDeviceWatch {
  type: 0;

  data: {
    stepCount?: { [date: DateType]: number[][] }; // every minute
    heartbeat?: { [date: DateType]: number[][] }; // every minute
    temp?: { [date: DateType]: number[][] }; // every minute
  };
  warn: {
    heartbeat?: { date: string; value: number }[];
    temp?: { date: string; value: number }[];
    fall?: string[];
  };
}

export interface IRawDeviceEnv {
  type: 1;

  data: {
    co?: { [date: DateType]: number[][] }; // every minute
    co2?: { [date: DateType]: number[][] }; // every minute
    pm2_5?: { [date: DateType]: number[][] }; // every minute
  };

  warn: {};
}

export interface IDeviceEnvWarn {
  co?: number;
  co2?: number;
  pm2_5?: number;
}
