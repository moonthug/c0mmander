import { Middleware } from 'koa';
import joi from 'joi';


const schema = joi.object({
  id: joi.number().min(0).max(11)
})

interface GetExecuteC0mmandMiddlewareCtxState {
  id: number;
}

/**
 *
 * @param ctx
 * @param next
 */
export const validationMiddleware: Middleware<GetExecuteC0mmandMiddlewareCtxState> = async (ctx, next) => {
  try {
    const { error } = schema.validate(
      ctx.params,
      { abortEarly: false }
    );

    if (error) throw error;

    ctx.state.id = parseInt(ctx.params.id, 10);

    await next();
  } catch (error) {
    // Logging
    throw error;
  }
}

/**
 *
 * @param ctx
 * @param next
 */
export const getExecuteC0mmandMiddleware: Middleware<GetExecuteC0mmandMiddlewareCtxState> = async (ctx, next) => {
  try {
    ctx.body = await ctx.c0mmandService.executeCommand(ctx.state.id);
  } catch (e) {
    throw e;
  }
  return next();
}

/**
 *
 */
export const getExecuteC0mmandMiddlewares = [
  validationMiddleware,
  getExecuteC0mmandMiddleware
]
