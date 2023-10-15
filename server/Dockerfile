FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY package.json .
RUN yarn install

FROM alpine:latest AS docs

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn
COPY --from=builder /app .
COPY . .
RUN yarn run swagger

FROM node:18

WORKDIR /app
COPY --from=docs /app/swagger-output.json .
COPY --from=builder /app .
COPY . .

EXPOSE 8000
CMD ["yarn", "start"]
