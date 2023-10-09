import path from 'path';
import { mkdirSync } from 'fs';

import { hasFile, readJsonFile, writeJsonFile } from '@/utils/file';

export const DATA_DIR = 'data';
export const TMP_DATA_PATH = path.join(DATA_DIR, 'tmp.json');
export const USERS_DATA_PATH = path.join(DATA_DIR, 'users.json');
export const DEVICES_DATA_PATH = path.join(DATA_DIR, 'devices.json');

export const init = () => {
  mkdirSync(DATA_DIR, { recursive: true });

  [USERS_DATA_PATH, DEVICES_DATA_PATH, TMP_DATA_PATH]
    .filter((d) => !hasFile(d))
    .forEach((d) => writeJsonFile(d));
};

export const getTmpConfig = () => {
  init();

  return readJsonFile<ITmpFile>(TMP_DATA_PATH);
};

export const nextLastUserID = () => {
  init();

  const data = getTmpConfig();
  data.lastUserID ??= '0';
  data.lastUserID = String(+data.lastUserID + 1);
  writeJsonFile(TMP_DATA_PATH, data);

  return data.lastUserID;
};

export const nextLastDeviceID = () => {
  init();

  const data = getTmpConfig();
  data.lastDeviceID ??= '0';
  data.lastDeviceID = String(+data.lastDeviceID + 1);
  writeJsonFile(TMP_DATA_PATH, data);

  return data.lastDeviceID;
};

export interface ITmpFile {
  lastUserID: string;
  lastDeviceID: string;
}
