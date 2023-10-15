import express from 'express';
import morgan from 'morgan';
import cors from 'cors';

import router from '@/router';
import { Context } from '@/router/utils/context';

export const createServer = () => {
  const app = express();
  const allowOrigins = process.env.ALLOWED_ORIGINS?.split(',');

  app.use(
    morgan('dev', { skip: (req) => req.originalUrl.startsWith('/docs') }),
  );
  app.use(cors({ origin: allowOrigins }));
  app.use(express.json()).use(express.urlencoded({ extended: false }));

  app.use(router);
  app.set('ctx', new Context());

  return app;
};
