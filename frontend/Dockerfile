FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY package.json .
RUN yarn install

FROM node:18

WORKDIR /app
COPY --from=builder /app .
COPY . .
RUN yarn build

EXPOSE 3000
CMD ["node", ".output/server/index.mjs"]
