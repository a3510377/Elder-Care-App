import { EventEmitter } from 'events';
import { Server, ServerOptions, WebSocket } from 'ws';

export class WebSocketClient extends EventEmitter {
  constructor(public readonly ws: WebSocket) {
    super();
  }

  send(data: string | object) {
    if (typeof data === 'object') data = JSON.stringify(data);

    this.ws.send(data);
  }
}

export class WebSocketServer extends Server {
  constructor(options: ServerOptions) {
    super(options);
    this.init();
  }

  init() {
    this.on('connection', (ws) => new WebSocketClient(ws));
  }

  sendAll(data: string | object | number) {
    if (typeof data === 'object') data = JSON.stringify(data);

    this.clients.forEach((client) => client.send(data as string));
  }
}
