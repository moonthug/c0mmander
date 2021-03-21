import Router from 'koa-router';
// import { postJobRouteMiddlewares } from './postJob';
import { getHealthMiddleware } from './getHealth';
import { getC0mmandsMiddlewares } from './getC0mmands';
import { getExecuteC0mmandMiddlewares } from './getExecuteC0mmand';

const router = new Router();
// router.use(handleErrorMiddleware);

router.get('/health', getHealthMiddleware);

router.get('/c0mmands', ...getC0mmandsMiddlewares);
router.get('/c0mmands/:id/execute', ...getExecuteC0mmandMiddlewares);

export default router;
