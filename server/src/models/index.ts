import { Connection, connect } from 'mongoose';

export class Database {
  connection!: Connection;
}

export let db: Database;

export const init = async () => {
  const url = process.env.DB_CONN_STRING ?? 'mongodb://localhost:27017';
  const username = process.env.DATABASE_USERNAME;
  const password = process.env.DATABASE_PASSWORD;

  const database = await connect(url, {
    dbName: 'elder-care-app',
    auth: { username, password },
    autoCreate: true,
    autoIndex: true,
  });

  db = { connection: database.connection };

  return db;
};

export * from './device';
export * from './user';
