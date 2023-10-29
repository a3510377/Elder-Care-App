FROM alpine:latest AS builder

WORKDIR /app
RUN apk add --no-cache --update nodejs yarn

COPY . .
RUN yarn install
RUN yarn build

FROM node:18

WORKDIR /app
COPY --from=builder /app/.output .
COPY --from=builder /app/.nuxt .

EXPOSE 3000
CMD ["node", ".output/server/index.mjs"]
