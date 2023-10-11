import { Server } from 'ws';

export class WebSocketServer extends Server {
  init() {}

  sendAll(event: string, message: string | number | object) {
    if (typeof message === 'object') message = JSON.stringify(message);

    this.clients.forEach((client) => client.send(message as string | number));
  }
}
