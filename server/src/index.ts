import dotenv from 'dotenv';
dotenv.config();

import { createApp } from './app';

const app = createApp();
app.listen(3000);
