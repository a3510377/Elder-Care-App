import axios from 'axios';
import { Server as SocketServer } from 'ws';

import { init } from './models';
import { createServer } from './utils/server';

process
  .on('uncaughtException', console.error)
  .on('unhandledRejection', console.error);

const main = async () => {
  await init();
  const { app, ctx } = createServer();
  const port = process.env.PORT ?? 8000;

  const server = app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port} `);
  });
  const ws = new SocketServer({ server });
  ws.on('connection', (client) => {
    const loop = setInterval(() => {
      client.send(JSON.stringify({ event: 'poll' }));
    }, 1e3 * 20);

    client.send(JSON.stringify({ event: 'link' }));
    client.on('close', () => clearInterval(loop));
  });
  ctx.on('fall', (user, now) => {
    const NOTIFY_TOKEN = process.env.NOTIFY_TOKEN;
    if (NOTIFY_TOKEN) {
      axios.post(
        'https://notify-api.line.me/api/notify',
        {
          message: `${user.name} 跌倒了!!  \n  手機：${user.phone}\n  地址：${user.address}`,
        },
        {
          headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            Authorization: `Bearer ${NOTIFY_TOKEN}`,
          },
        },
      );
    }

    ws.clients.forEach((client) => {
      client.send(JSON.stringify({ event: 'fall', data: { user, now } }));
    });
  });
};

main();
