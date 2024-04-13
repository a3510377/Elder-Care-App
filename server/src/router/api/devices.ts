import { Router } from 'express';

import { HttpStatus, ResponseStatus, sendResponse } from '../utils';
import { getDate, getHour, getMinute } from '@/utils/utils';
import { Context } from '../utils/context';
import {
  DeviceModel,
  IDeviceEnvWarn,
  IRawDeviceWatch,
  UserModel,
} from '@/models';

export const router = Router();

export interface RegisterDeviceData {
  type: 0 | 1;
  user_id: string;
}

router.post('/', async (req, res) => {
  // #swagger.tags = ['Devices']
  // #swagger.description = 'Register a new device'
  /* #swagger.requestBody = {
    description: 'Description',
    content: {
      'application/json': {
        schema: { $ref: '#/components/schemas/RegisterDeviceData' },
      }
    }
  } */
  const { type, user_id }: RegisterDeviceData = req.body;
  if (type === undefined || !user_id) {
    /* #swagger.responses[400] = {
      description: "Missing required parameter 'type' or 'user_id'",
      schema: { code: 1 }
    } */
    return sendResponse(
      res,
      {
        code: ResponseStatus.MISSING_ARGUMENT,
        body: { message: "Missing required parameter 'type' or 'user_id'" },
      },
      HttpStatus.BAD_REQUEST,
    );
  }
  try {
    /* #swagger.responses[200] = {
      description: 'Successful operation',
      schema: { $ref: '#/components/schemas/Device' }
    } */
    const user = await UserModel.findById(user_id).catch(() => null);
    if (!user) {
      throw new Error('User is not found');
    }

    const device = await new DeviceModel({ type }).save();

    user.device.push(device._id);
    await user.save();

    sendResponse(res, { body: device.getPublicInfo() });
  } catch (e) {
    /* #swagger.responses[400] = {
      description: "invalid user_id",
      schema: { code: 1 }
    } */
    return sendResponse(
      res,
      { code: ResponseStatus.MISSING_ARGUMENT, body: { message: e } },
      HttpStatus.BAD_REQUEST,
    );
  }
});

router.get('/:id', async (req, res) => {
  // #swagger.tags = ['Devices']
  // #swagger.description = 'Get device from id'

  const device = await DeviceModel.findById(req.params.id).catch(() => null);
  if (!device) {
    /* #swagger.responses[404] = {
      description: 'Device not found',
      schema: { code: 2 }
    } */
    return sendResponse(
      res,
      { code: ResponseStatus.NOT_FOUND },
      HttpStatus.NOT_FOUND,
    );
  }

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { $ref: '#/components/schemas/Device' }
  } */
  sendResponse(res, { body: device.getPublicInfo() });
});

router.post('/:id', async (req, res) => {
  // #swagger.tags = ['Devices']
  // #swagger.description = 'Add device data'

  const id = req.params.id;
  const device = await DeviceModel.findById(id).catch(() => null);
  if (!device) {
    /* #swagger.responses[404] = {
      description: 'Device not found',
      schema: { code: 2 }
    } */
    return sendResponse(
      res,
      { code: ResponseStatus.NOT_FOUND },
      HttpStatus.NOT_FOUND,
    );
  }

  const data: Record<string, number> = req.body;
  const { type } = device;
  if (type === 0) {
    const { stepCount, heartbeat, temp } = data;

    device.data ||= {};
    const deviceData = device.data;
    for (const [key, value] of Object.entries({
      stepCount,
      heartbeat,
      temp,
    })) {
      if (value !== undefined) {
        const date = getDate();
        const hour = getHour();
        const minute = getMinute();

        // @ts-ignore
        deviceData[key] ||= {};
        // @ts-ignore
        deviceData[key][date] ||= [];
        // @ts-ignore
        deviceData[key][date][hour] ||= [];
        // @ts-ignore
        deviceData[key][date][hour][minute] = value;
      }
    }

    const warn: any = data.warn;
    device.warn ||= {};
    const warnData = device.warn as IRawDeviceWatch['warn'];
    if (warn) {
      if (warn.heartbeat) {
        warnData.heartbeat ||= [];
        warnData.heartbeat.push({
          date: new Date().toISOString(),
          value: warn.heartbeat,
        });
      }

      if (warn.temp) {
        warnData.temp ||= [];
        warnData.temp.push({
          date: new Date().toISOString(),
          value: warn.temp,
        });
      }

      if (warn.fall) {
        const now = new Date();
        const context: Context = res.app.get('ctx');

        const user = await UserModel.findOne({
          device: { $in: device._id },
        }).catch(() => null);

        if (user) {
          context.emit('fall', user.getPublicInfo(), now);
        }

        warnData.fall ||= [];
        warnData.fall.push(now.toISOString());
      }
    }

    await device.save();
  } else if (type === 1) {
    const { co, co2, pm2_5 } = data;

    device.data ||= {};
    const deviceData = device.data;
    for (const [key, value] of Object.entries({ co, co2, pm2_5 })) {
      if (value !== undefined) {
        const date = getDate();
        const hour = getHour();
        const minute = getMinute();

        // @ts-ignore
        deviceData[key] ||= {};
        // @ts-ignore
        deviceData[key][date] ||= [];
        // @ts-ignore
        deviceData[key][date][hour] ||= [];
        // @ts-ignore
        deviceData[key][date][hour][minute] = value;
      }
    }

    const warn: any = data.warn;
    device.warn ||= {};
    if (warn) {
      const context: Context = res.app.get('ctx');
      const user = await UserModel.findOne({
        device: { $in: device._id },
      }).catch(() => null);

      if (user) {
        const warnData: IDeviceEnvWarn = {};
        if (warn.co) warnData.co = co;
        if (warn.co2) warnData.co2 = co2;
        if (warn.pm2_5) warnData.pm2_5 = pm2_5;

        if (Object.keys(user).length) {
          context.emit('warn', user.getPublicInfo(), warnData);
        }
      }
    }

    await device.save();
    // TODO add device type 1 handler
    // export interface IFileDeviceEnv {
    //   type: 1;
    //   user_id: string;
    //   airQuality?: { [date: DateType]: IAirQualityData[][] }; // every minute
    //   humidity?: { [date: DateType]: number[][] }; // every minute
    //   temp?: { [date: DateType]: number[][] }; // every minute
    //   warn: {
    //     airQuality?: ({ date: Date } & IAirQualityData)[];
    //     harmfulGas?: { date: Date; value: number }[];
    //   };
    // }
  } else {
    // TODO send "Invalid device type" error
  }

  /* #swagger.responses[200] = {
    description: 'Successful operation',
    schema: { $ref: '#/components/schemas/Device' }
  } */
  sendResponse(res, { body: device.getPublicInfo() });
});

export default router;
