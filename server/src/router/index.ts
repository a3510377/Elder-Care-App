import { Router } from 'express';
import swaggerUI from 'swagger-ui-express';

import api from './api';
import swaggerOutput from 'swagger-output.json';

export const router = Router();

router.use('/docs', swaggerUI.serve, swaggerUI.setup(swaggerOutput));
router.use('/api', api);

export default router;

export * from './utils/';
