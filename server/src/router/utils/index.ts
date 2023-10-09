import { Response } from 'express';

import { HttpStatus, ResponseStatus } from './code';

export interface APIRequestBody<T> {
  code: ResponseStatus;
  body?: T;
}

export const sendResponse = <T>(
  res: Response,
  body?: Partial<APIRequestBody<T>>,
  status = HttpStatus.OK,
) => {
  res.status(status).json(<APIRequestBody<T>>{
    code: ResponseStatus.SUCCESS,
    ...(body || {}),
  });
};

export * from './code';
