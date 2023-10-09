FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY package.json .
RUN yarn install --prod

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app .
COPY . .
RUN yarn swagger

CMD ["yarn", "start"]
