FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY package.json .
RUN yarn install --prod
RUN yarn swagger

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app .
COPY . .

CMD ["yarn", "start"]
