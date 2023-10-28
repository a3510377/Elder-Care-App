import { init } from './models';
import { createServer } from './utils/server';

process
  .on('uncaughtException', console.error)
  .on('unhandledRejection', console.error);

const main = async () => {
  await init();
  const app = createServer();
  const port = process.env.PORT ?? 8000;

  app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port} `);
  });
};

main();
