import { Router } from 'express';
import multer from 'multer';
import sharp from 'sharp';
import * as blurhash from 'blurhash';

import { HttpStatus, ResponseStatus, sendResponse } from '..';
import { UserModel } from '@/models';

export const router = Router();
const avatarUpload = multer({
  fileFilter(req, file, cb) {
    if (!file.originalname.match(/\.(jpg|jpeg|png)$/)) {
      cb(new Error('Please upload an image'));
    }
    cb(null, true);
  },
  // The file size limits to 1MB.
  limits: { fileSize: 1000000 },
});

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

router.post('/:id/avatar', avatarUpload.single('avatar'), async (req, res) => {
  const file = req.file;

  if (!file || !file.size) {
    /* #swagger.responses[400] = {
        description: 'The user avatar file is missing or invalid',
        schema: { code: 3 }
      } */
    return sendResponse(
      res,
      { code: ResponseStatus.INVALID_USER_AVATAR_FILE },
      HttpStatus.BAD_REQUEST,
    );
  }

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

  const { data, info } = await sharp(file.buffer).ensureAlpha().raw().toBuffer({
    resolveWithObject: true,
  });
  const avatar_hash = blurhash.encode(
    new Uint8ClampedArray(data),
    info.width,
    info.height,
    5,
    5,
  );
  console.log(avatar_hash);

  user.avatar = file.buffer;
  user.avatar_hash = avatar_hash;

  await user.save();

  /* #swagger.responses[200] = {
      description: 'Successful operation',
      schema: { code: 0, body: {} }
    } */
  return sendResponse(res, { body: { avatar_hash } });
});

router.get('/:id/avatar', async (req, res) => {
  const user = await UserModel.findById(req.params.id).catch(() => null);
  const avatar = user?.avatar;
  if (!avatar) {
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
  } */
  res.setHeader('Content-Type', 'image');
  res.send(avatar);
});

export default router;
