import { Router } from 'express';

import { HttpStatus, ResponseStatus, sendResponse } from '..';
import { createUser, getUserFromID, getUsers } from '@/data/user';

export const router = Router();

export interface SignUpUserData {
  name: string;
  address?: string;
}

router.get('/', (req, res) => {
  // #swagger.tags = ['Users']
  // #swagger.description = 'Get users'

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { $ref: '#/components/schemas/Users' }
  } */
  sendResponse(res, { body: getUsers() });
});

router.post('/', (req, res) => {
  // #swagger.tags = ['Users']
  // #swagger.description = 'Create a new user'
  /* #swagger.requestBody = {
    description: 'Description',
    content: {
      'application/json': {
        schema: { $ref: '#/components/schemas/SignUpUserData' },
      }
    }
  } */
  const data: SignUpUserData = req.body;
  const { name, address } = data;

  if (!name) {
    /* #swagger.responses[400] = {
      description: "Missing required parameter 'name'",
      schema: { code: 1 }
    } */
    return sendResponse(
      res,
      {
        code: ResponseStatus.MISSING_ARGUMENT,
        body: { message: "Missing required parameter 'name'" },
      },
      HttpStatus.BAD_REQUEST,
    );
  }

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { code: 1, body: { $ref: '#/components/schemas/User' } }
  } */
  sendResponse(res, { body: createUser(name, address || '') });
});

router.get('/:id', (req, res) => {
  // #swagger.tags = ['Users']
  // #swagger.description = 'Get user from id'
  const user = getUserFromID(req.params.id);

  if (!user) {
    /* #swagger.responses[404] = {
      description: 'User not found',
      schema: { code: 2 }
    } */
    return sendResponse(
      res,
      { code: ResponseStatus.NOT_FOUND },
      HttpStatus.NOT_FOUND,
    );
  }
  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { code: 0, body: { $ref: '#/components/schemas/User' } }
  } */
  sendResponse(res, { body: user });
});

export default router;
