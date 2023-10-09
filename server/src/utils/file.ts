import fs from 'fs';

export const readStringFile = (path: string) => {
  return fs.readFileSync(path).toString();
};

export const readJsonFile = <T>(path: string): T => {
  return JSON.parse(readStringFile(path));
};

export const writeJsonFile = <T = unknown>(path: string, data: T = <T>{}) => {
  fs.writeFileSync(path, JSON.stringify(data));
};

export const hasFile = (path: string) => {
  try {
    return fs.statSync(path).isFile();
  } catch {
    return false;
  }
};

export const hasDir = (path: string) => {
  try {
    return fs.statSync(path).isDirectory();
  } catch {
    return false;
  }
};
