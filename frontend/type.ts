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

export interface User {
  id: string;
  name: string;
  address: string;
  devices: string[];
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

  user_id: string;
  stepCount?: { [date: DateType]: number[][] }; // every minute
  heartbeat?: { [date: DateType]: number[][] }; // every minute
  temp?: { [date: DateType]: number[][] }; // every minute

  warn: {
    heartbeat?: { date: string; value: number }[];
    temp?: { date: string; value: number }[];
    fall?: string[];
  };
}

export interface IDeviceEnv {
  id: string;
  type: 1;

  user_id: string;
  airQuality?: { [date: DateType]: IAirQualityData[][] }; // every minute
  humidity?: { [date: DateType]: number[][] }; // every minute
  temp?: { [date: DateType]: number[][] }; // every minute

  warn: {
    airQuality?: ({ date: string } & IAirQualityData)[];
    harmfulGas?: { date: string; value: number }[];
  };
}
