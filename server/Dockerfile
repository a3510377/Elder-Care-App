FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY package.json .
RUN yarn install --prod

FROM alpine:latest AS docs

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn
RUN yarn install
RUN yarn swagger

FROM alpine:latest

WORKDIR /app
COPY --from=docs /app/swagger-output.json .
COPY --from=builder /app .
COPY . .

CMD ["yarn", "start"]
