import { IUser } from '@/models';
import { EventEmitter } from 'events';

export class Context extends EventEmitter implements Context {}

export interface Context {
  addListener<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;

  on<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;

  once<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;

  removeListener<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;

  off<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;

  removeAllListeners<K extends keyof EventsTypes>(event?: K): this;

  listeners<K extends keyof EventsTypes>(eventName: K): Function[];

  rawListeners<K extends keyof EventsTypes>(eventName: K): Function[];

  emit<K extends keyof EventsTypes>(
    eventName: K,
    ...args: EventsTypes[K]
  ): boolean;

  listenerCount<K extends keyof EventsTypes>(
    eventName: K,
    listener?: Function,
  ): number;

  prependListener<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;

  prependOnceListener<K extends keyof EventsTypes>(
    eventName: K,
    listener: (...args: EventsTypes[K]) => void,
  ): this;
}

export interface EventsTypes {
  fall: [user: IUser[], date: Date];
}
