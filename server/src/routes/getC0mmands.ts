import Koa, { Middleware } from 'koa';

/**
 *
 * @param ctx
 * @param next
 */
export const getC0mmandsMiddleware: Middleware = async (ctx, next) => {
  try {
    ctx.body = await ctx.c0mmandService.getC0mmands();
  } catch (e) {
    throw e;
  }
  return next();
}

/**
 *
 */
export const getC0mmandsMiddlewares = [
  getC0mmandsMiddleware
]
