import http from 'http';

import { init } from './data';
import { WebSocketServer } from './utils/ws';
import { createServer } from './utils/server';

process
  .on('uncaughtException', console.error)
  .on('unhandledRejection', console.error);

const main = () => {
  init();
  const app = createServer();
  const server = http.createServer(app);
  const ws = new WebSocketServer({ server });
  const port = process.env.PORT ?? 8000;

  app.set('ws', ws);
  app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port} `);
  });
};

main();
