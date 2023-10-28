import { Router } from 'express';

import { HttpStatus, ResponseStatus, sendResponse } from '..';
import { UserModel } from '@/models';

export const router = Router();

export interface SignUpUserData {
  name: string;
  address?: string;
}

router.get('/', async (req, res) => {
  // #swagger.tags = ['Users']
  // #swagger.description = 'Get users'
  const users = await UserModel.find();

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { $ref: '#/components/schemas/Users' }
  } */
  sendResponse(res, { body: users.map((d) => d.getPublicInfo()) });
});

router.post('/', async (req, res) => {
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

  if (!name || !address) {
    /* #swagger.responses[400] = {
      description: "Missing required parameter 'name'",
      schema: { code: 1 }
    } */
    return sendResponse(
      res,
      {
        code: ResponseStatus.MISSING_ARGUMENT,
        body: { message: "Missing required parameter 'name', 'address'" },
      },
      HttpStatus.BAD_REQUEST,
    );
  }

  const user = await new UserModel({ name, address }).save();

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { code: 1, body: { $ref: '#/components/schemas/User' } }
  } */
  sendResponse(res, { body: user.getPublicInfo() });
});

router.get('/:id', async (req, res) => {
  // #swagger.tags = ['Users']
  // #swagger.description = 'Get user from id'
  const user = await UserModel.findById(req.params.id).catch(() => null);

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
  sendResponse(res, { body: user.getPublicInfo() });
});

export default router;
