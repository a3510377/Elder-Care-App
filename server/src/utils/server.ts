import express from 'express';
import morgan from 'morgan';
import cors from 'cors';

import router from '@/router';

export const createServer = () => {
  const app = express();
  const allowOrigins = process.env.ALLOWED_ORIGINS?.split(',');

  app.use(morgan('dev')).use(cors({ origin: allowOrigins }));
  app.use(express.json()).use(express.urlencoded({ extended: false }));

  app.use(router);

  return app;
};
