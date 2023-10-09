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
    server: [
      {
        url: 'http://localhost:8080',
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
      },
    },
  },
);
