import { Middleware } from 'koa';

export const getHealthMiddleware: Middleware = (ctx, next) => {
  ctx.body = 'ok';
};
