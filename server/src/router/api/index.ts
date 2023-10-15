import { Router } from 'express';

import users from './users';
import devices from './devices';
import { Context } from '../utils/Context';

export const router = Router();

router.use('/users', users);
router.use('/devices', devices);
router.get('/', (req, res) => {
  res.set({
    'Content-Type': 'text/event-stream',
    'Cache-Control': 'no-cache',
    Connection: 'keep-alive',
  });

  res.write(`retry: 1500\n\n`);

  const context: Context = res.app.get('ctx');
  context.on('fall', (user, now) => {
    res.write(`event: fall\ndata:${JSON.stringify({ user, now })}\n\n`);
  });
});

export default router;
