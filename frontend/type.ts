import type { RouteLocationRaw } from 'vue-router';

export type MenuItem = MenuLinkItem | MenuButtonItem | MenuDropdownItem;

export interface BaseMenuItem {
  title: string;
}

export interface MenuLinkItem extends BaseMenuItem {
  type: 'link';
  to: RouteLocationRaw;
}

export interface MenuButtonItem extends BaseMenuItem {
  type: 'button';
}

export interface MenuDropdownItem extends BaseMenuItem {
  type: 'dropdown';
  children: (MenuLinkItem | MenuButtonItem)[];
}

export interface APIRequestBody<T> {
  code: number;
  body?: T;
}

export enum GenderType {
  Male,
  Female,
}

export interface User {
  id: string;
  name: string;
  age: number;
  phone: String;
  gender: GenderType;
  remark: string;
  address: string;
  device: string[];
  password: string;
  avatar: Buffer;
  avatar_hash: String;
}

export interface WarnData {
  user: User;
  message: string;
}

export type DateType = `${string}/${string}/${string}`; // YYYY-MM-DD

export type Device = IDeviceWatch | IDeviceEnv;

export type DeviceTypes = Device['type'];

export interface IAirQualityData {
  type: '10' | '1.0' | '2.5';
  value: number;
}

export interface IDeviceWatch {
  id: string;
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

export interface IDeviceEnv {
  id: string;
  type: 1;

  data: {
    co?: { [date: DateType]: number[][] }; // every minute
    co2?: { [date: DateType]: number[][] }; // every minute
    pm2_5?: { [date: DateType]: number[][] }; // every minute
  };

  warn: {
    airQuality?: ({ date: string } & IAirQualityData)[];
    harmfulGas?: { date: string; value: number }[];
  };
}

export interface IDeviceEnvWarn {
  co?: number;
  co2?: number;
  pm2_5?: number;
}

export interface IAlarm {
  user?: User;
  message: string;
}
