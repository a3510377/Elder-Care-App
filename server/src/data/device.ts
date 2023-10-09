export type IFileDevices = { [device_id: string]: IFileDevice };

export type IFileDevice = IFileDeviceWatch | IFileDeviceEnv;

export type DateType = `${string}/${string}/${string}`; // YYYY-MM-DD

export interface IAirQualityData {
  type: '10' | '1.0' | '2.5';
  value: number;
}

export interface IFileDeviceWatch {
  type: 0;
  stepCount: { [date: DateType]: number[] }; // every minute
  heartbeat: { [date: DateType]: number[] }; // every minute
  temp: { [date: DateType]: number[] }; // every minute
  warn: {
    heartbeat: { date: Date; value: number }[];
    temp: { date: Date; value: number }[];
    fall: Date[];
  };
}

export interface IFileDeviceEnv {
  type: 1;

  airQuality: { [date: DateType]: IAirQualityData[] }; // every minute
  humidity: { [date: DateType]: number[] }; // every minute
  temp: { [date: DateType]: number[] }; // every minute

  warn: {
    airQuality: ({ date: Date } & IAirQualityData)[];
    harmfulGas: { date: Date; value: number }[];
  };
}
