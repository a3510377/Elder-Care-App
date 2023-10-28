import { Model, Schema, Types, model } from 'mongoose';
import { DeviceModel } from './device';

export const UserSchema = new Schema<
  IUser,
  Model<IUser, {}, IUserMethods>,
  IUserMethods
>({
  name: { type: String, required: true },
  address: { type: String, required: true },
  device: { type: [Types.ObjectId], ref: DeviceModel },
  password: { type: String, required: false },
  avatar: { type: Buffer, required: false },
  avatar_hash: { type: String, required: false },
});

UserSchema.method('getPublicInfo', function (): IPublicUser {
  return {
    id: this.id,
    name: this.name,
    address: this.address,
    device: this.device,
    avatar_hash: this.avatar_hash,
  };
});

export const UserModel = model('user', UserSchema, void 0, {
  overwriteModels: true,
});

export interface IUserMethods {
  /**Get user public info data */
  getPublicInfo(): IPublicUser;
}

export interface IUser {
  name: string;
  address: string;
  device: Types.ObjectId[];
  password: string;
  avatar: Buffer;
  avatar_hash: String;
}

export interface IPublicUser extends Omit<IUser, 'password' | 'avatar'> {
  id: Types.ObjectId;
}
