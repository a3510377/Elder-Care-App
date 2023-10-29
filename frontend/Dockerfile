FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY . .
RUN yarn install
RUN yarn build

EXPOSE 3000
CMD ["node", ".output/server/index.mjs"]
