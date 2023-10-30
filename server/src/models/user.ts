import { Model, Schema, Types, model } from 'mongoose';
import { DeviceModel } from './device';

export enum GenderType {
  Male,
  Female,
}

export const UserSchema = new Schema<
  IUser,
  Model<IUser, {}, IUserMethods>,
  IUserMethods
>({
  name: { type: String, required: true },
  age: Number,
  phone: String,
  gender: { type: Number, enum: GenderType, default: GenderType.Male },
  remark: String,
  address: { type: String, required: true },
  device: { type: [Types.ObjectId], ref: DeviceModel },
  password: { type: String, required: false },
  avatar: { type: Buffer, required: false },
  avatar_hash: { type: String, required: false },
});

UserSchema.method('getPublicInfo', function (): IPublicUser {
  return {
    id: this.id,
    age: this.age,
    phone: this.phone,
    gender: this.gender,
    remark: this.remark,
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
  age: number;
  phone: String;
  gender: GenderType;
  remark: string;
  address: string;
  device: Types.ObjectId[];
  password: string;
  avatar: Buffer;
  avatar_hash: String;
}

export interface IPublicUser extends Omit<IUser, 'password' | 'avatar'> {
  id: Types.ObjectId;
}
