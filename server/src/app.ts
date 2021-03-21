import Koa from 'koa';
import { StatusCodes } from 'http-status-codes';
import { C0mmandService } from './services/C0mmandService';
import router from './routes';

export interface AppContext extends Koa.Context {
  c0mmandService: C0mmandService;
}

export interface AppState extends Koa.DefaultState {
}

export function createApp() {
  const app = new Koa<AppState, AppContext>();

  // Generic error handling middleware.
  app.use(async (ctx: Koa.Context, next: () => Promise<any>) => {
    try {
      await next();
    } catch (error) {
      ctx.status = error.statusCode || error.status || StatusCodes.INTERNAL_SERVER_ERROR;
      error.status = ctx.status;
      ctx.body = { error };
      ctx.app.emit('error', error, ctx);
    }
  });

  app.context.c0mmandService = new C0mmandService();

  app.use(router.routes());

  app.on('error', console.error);

  return app;
}
