import { init } from './data';
import { WebSocketServer } from './utils/gateway';
import { createServer } from './utils/server';

process
  .on('uncaughtException', console.error)
  .on('unhandledRejection', console.error);

const main = () => {
  init();
  const app = createServer();
  const port = process.env.PORT ?? 8000;

  const server = app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port} `);
  });
  const ws = new WebSocketServer({ server, path: '/api/gateway' });
  ws.init();
  app.set('ws', ws);
};

main();
