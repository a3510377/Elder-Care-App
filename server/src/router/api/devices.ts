import { Router } from 'express';

import { sendResponse } from '../utils';

export const router = Router();

export interface RegisterDeviceData {
  name: string;
  type: 0 | 1;
  user_id: string;
}

router.get('/:id', (req, res) => {
  // #swagger.tags = ['Devices']
  // #swagger.description = 'Get device from id'

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { $ref: '#/components/schemas/Device' }
  } */
  sendResponse(res, {});
});

router.post('/:id', (req, res) => {
  // #swagger.tags = ['Devices']
  // #swagger.description = 'Get device from id'

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { $ref: '#/components/schemas/Device' }
  } */
  sendResponse(res, {});
});

export default router;
