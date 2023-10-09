import { readJsonFile, writeJsonFile } from '@/utils/file';
import { init, USERS_DATA_PATH, nextLastUserID } from '.';

export type IFileUsers = { [user_id: string]: IFileUser };

export interface IFileUser {
  name: string;
  address: string;
  devices: string[];
}

export interface IUser extends Omit<IFileUser, 'devices'> {
  id: string;
}

export const readUserFile = () => {
  init();

  return readJsonFile<IFileUsers>(USERS_DATA_PATH);
};

export const createUser = (name: string, address: string): IUser => {
  const data = readUserFile();
  const id = nextLastUserID();

  data[id] = { name, address, devices: [] };
  writeJsonFile(USERS_DATA_PATH, data);

  return { ...data[id], id };
};

export const getUsers = (): IUser[] => {
  return Object.entries(readUserFile()).map(([id, user]) => ({ id, ...user }));
};

export const getUserFromID = (id: string): IUser | undefined => {
  const user = readUserFile()[id];

  return user ? { id, ...user } : void 0;
};
