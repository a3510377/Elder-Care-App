import swagger from 'swagger-autogen';
import { path } from 'app-root-path';

swagger({ openapi: '3.1.0' })(
  `${path}/swagger-output.json`,
  [`${path}/src/router/index.ts`],
  {
    info: {
      title: 'Elder Care App Docs',
      version: '0.0.1',
      description: 'This is a REST API For Elder Care App',
    },
    servers: [
      {
        url: 'http://localhost:8000',
        description: 'Internal server for testing',
      },
    ],
    tags: ['User', 'Device'],
    components: {
      '@schemas': {
        User: {
          type: 'object',
          description: 'User',
          properties: {
            id: { type: 'string', example: '0' },
            name: { type: 'string', example: 'XXX老先生' },
            address: { type: 'string', example: '台南市XX區XX里XX之XX號' },
            devices: { type: 'array', item: 'string', example: ['1', '20'] },
          },
        },
        Users: {
          type: 'array',
          description: 'User list',
          items: { $ref: '#/components/schemas/User' },
        },
        SignUpUserData: {
          type: 'object',
          description: 'The data for signing up user',
          required: ['name'],
          properties: {
            name: { type: 'string', example: 'XXX老先生' },
            address: { type: 'string', example: '台南市XX區XX里XX之XX號' },
          },
        },

        AirQualityData: {
          type: 'object',
          properties: {
            type: { type: 'string', enum: ['10', '1.0', '2.5'] },
            value: { type: 'number' },
          },
        },

        RegisterDeviceData: {
          type: 'object',
          required: ['type', 'user_id'],
          properties: {
            type: { $ref: '#/components/schemas/DeviceType' },
            user_id: { type: 'string', example: '0' },
          },
        },

        Device: {
          oneOf: [
            { $ref: '#/components/schemas/DeviceWatch' },
            { $ref: '#/components/schemas/DeviceEnv' },
          ],
        },

        DeviceType: {
          type: 'number',
          enum: [0, 1],
          description: 'Device Type:\n* `0` - Watch\n* `1` - Env',
        },
        DeviceWatch: {
          type: 'object',
          properties: {
            type: { $ref: '#/components/schemas/DeviceType', example: 0 },
            stepCount: {
              type: 'object',
              additionalProperties: {
                type: 'array',
                description: 'event minute',
                items: { type: 'number' },
              },
            },
            heartbeat: {
              type: 'object',
              additionalProperties: {
                type: 'array',
                description: 'event minute',
                items: { type: 'number' },
              },
            },
            temp: {
              type: 'object',
              additionalProperties: {
                type: 'array',
                description: 'event minute',
                items: { type: 'number' },
              },
            },
            warn: {
              type: 'object',
              description: 'warn log',
              properties: {
                heartbeat: {
                  type: 'array',
                  items: {
                    type: 'object',
                    properties: {
                      date: {
                        type: 'string',
                        example: '2023-09-30T16:00:00.000Z',
                      },
                      value: { type: 'number' },
                    },
                  },
                },
                temp: {
                  type: 'array',
                  items: {
                    type: 'object',
                    properties: {
                      date: {
                        type: 'string',
                        example: '2023-09-30T16:00:00.000Z',
                      },
                      value: { type: 'number' },
                    },
                  },
                },
                fall: { type: 'array', items: { type: 'string' } },
              },
            },
          },
        },
        DeviceEnv: {
          type: 'object',
          properties: {
            type: { $ref: '#/components/schemas/DeviceType', example: 1 },
            airQuality: {
              type: 'object',
              additionalProperties: {
                type: 'array',
                description: 'event minute',
                items: { $ref: '#/components/schemas/AirQualityData' },
              },
            },
            humidity: {
              type: 'object',
              additionalProperties: {
                type: 'array',
                description: 'event minute',
                items: { type: 'number' },
              },
            },
            temp: {
              type: 'object',
              additionalProperties: {
                type: 'array',
                description: 'event minute',
                items: { type: 'number' },
              },
            },
            warn: {
              type: 'object',
              description: 'warn log',
              properties: {
                airQuality: {
                  type: 'array',
                  items: {
                    allOf: [
                      { $ref: '#/components/schemas/AirQualityData' },
                      {
                        type: 'object',
                        properties: {
                          date: {
                            type: 'string',
                            example: '2023-09-30T16:00:00.000Z',
                          },
                        },
                      },
                    ],
                  },
                },
                harmfulGas: {
                  type: 'array',
                  items: {
                    type: 'object',
                    properties: {
                      date: {
                        type: 'string',
                        example: '2023-09-30T16:00:00.000Z',
                      },
                      value: { type: 'number' },
                    },
                  },
                },
              },
            },
          },
        },
      },
    },
  },
);
