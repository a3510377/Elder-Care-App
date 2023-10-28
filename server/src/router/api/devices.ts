import { Router } from 'express';

import { HttpStatus, ResponseStatus, sendResponse } from '../utils';
import { getDate, getHour, getMinute } from '@/utils/utils';
import { Context } from '../utils/context';

export const router = Router();

// export interface RegisterDeviceData {
//   type: 0 | 1;
//   user_id: string;
// }

// export interface RegisterDeviceData {
//   type: 0 | 1;
//   user_id: string;
// }

// router.post('/', (req, res) => {
//   // #swagger.tags = ['Devices']
//   // #swagger.description = 'Register a new device'
//   /* #swagger.requestBody = {
//     description: 'Description',
//     content: {
//       'application/json': {
//         schema: { $ref: '#/components/schemas/RegisterDeviceData' },
//       }
//     }
//   } */
//   const { type, user_id }: RegisterDeviceData = req.body;
//   if (type === undefined || user_id === undefined) {
//     /* #swagger.responses[400] = {
//       description: "Missing required parameter 'type' or 'user_id'",
//       schema: { code: 1 }
//     } */
//     return sendResponse(
//       res,
//       {
//         code: ResponseStatus.MISSING_ARGUMENT,
//         body: { message: "Missing required parameter 'type' or 'user_id'" },
//       },
//       HttpStatus.BAD_REQUEST,
//     );
//   }
//   try {
//     /* #swagger.responses[200] = {
//       description: 'Successful operation',
//       schema: { $ref: '#/components/schemas/Device' }
//     } */
//     sendResponse(res, { body: createDevice(type, user_id) });
//   } catch (e) {
//     /* #swagger.responses[400] = {
//       description: "invalid user_id",
//       schema: { code: 1 }
//     } */
//     return sendResponse(
//       res,
//       { code: ResponseStatus.MISSING_ARGUMENT, body: { message: e } },
//       HttpStatus.BAD_REQUEST,
//     );
//   }
// });

// router.get('/:id', (req, res) => {
//   // #swagger.tags = ['Devices']
//   // #swagger.description = 'Get device from id'

//   const device = getDeviceFromID(req.params.id);
//   if (!device) {
//     /* #swagger.responses[404] = {
//       description: 'Device not found',
//       schema: { code: 2 }
//     } */
//     return sendResponse(
//       res,
//       { code: ResponseStatus.NOT_FOUND },
//       HttpStatus.NOT_FOUND,
//     );
//   }

//   /* #swagger.responses[200] = {
//     description: 'Successful operation',
//     schema: { $ref: '#/components/schemas/Device' }
//   } */
//   sendResponse(res, { body: device });
// });

// router.post('/:id', (req, res) => {
//   // #swagger.tags = ['Devices']
//   // #swagger.description = 'Add device data'

//   const id = req.params.id;
//   const device = getDeviceFromID(id);
//   if (!device) {
//     /* #swagger.responses[404] = {
//       description: 'Device not found',
//       schema: { code: 2 }
//     } */
//     return sendResponse(
//       res,
//       { code: ResponseStatus.NOT_FOUND },
//       HttpStatus.NOT_FOUND,
//     );
//   }

//   const user = getUserFromID(device.user_id);
//   if (!user) {
//     /* #swagger.responses[404] = {
//       description: 'User not found',
//       schema: { code: 2 }
//     } */
//     return sendResponse(
//       res,
//       { code: ResponseStatus.NOT_FOUND },
//       HttpStatus.NOT_FOUND,
//     );
//   }

//   const data: Record<string, number> = req.body;
//   const { type } = device;
//   if (type === 0) {
//     const { stepCount, heartbeat, temp } = data;

//     for (const [key, value] of Object.entries({ stepCount, heartbeat, temp })) {
//       if (value !== undefined) {
//         const date = getDate();
//         const hour = getHour();
//         const minute = getMinute();

//         // @ts-ignore
//         device[key] ||= {};
//         // @ts-ignore
//         device[key][date] ||= [];
//         // @ts-ignore
//         device[key][date][hour] ||= [];
//         // @ts-ignore
//         device[key][date][hour][minute] = value;
//       }
//     }

//     const warn: any = data.warn;
//     const warnData = device.warn;
//     if (warn) {
//       if (warn.heartbeat) {
//         warnData.heartbeat ||= [];
//         warnData.heartbeat.push({
//           date: new Date().toISOString(),
//           value: warn.heartbeat,
//         });
//       }

//       if (warn.temp) {
//         warnData.temp ||= [];
//         warnData.temp.push({
//           date: new Date().toISOString(),
//           value: warn.temp,
//         });
//       }

//       if (warn.fall) {
//         const now = new Date();
//         const context: Context = res.app.get('ctx');

//         context.emit('fall', user, now);
//         warnData.fall ||= [];
//         warnData.fall.push(now.toISOString());
//       }
//     }

//     writeDeviceFromID(id, device);
//   } else if (type === 1) {
//     // TODO add device type 1 handler
//     // export interface IFileDeviceEnv {
//     //   type: 1;
//     //   user_id: string;
//     //   airQuality?: { [date: DateType]: IAirQualityData[][] }; // every minute
//     //   humidity?: { [date: DateType]: number[][] }; // every minute
//     //   temp?: { [date: DateType]: number[][] }; // every minute
//     //   warn: {
//     //     airQuality?: ({ date: Date } & IAirQualityData)[];
//     //     harmfulGas?: { date: Date; value: number }[];
//     //   };
//     // }
//   } else {
//     // TODO send "Invalid device type" error
//   }

//   /* #swagger.responses[200] = {
//     description: 'Successful operation',
//     schema: { $ref: '#/components/schemas/Device' }
//   } */
//   sendResponse(res, { body: device });
// });

export default router;
