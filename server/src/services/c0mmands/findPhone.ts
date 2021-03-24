import twilio from 'twilio';
import { C0mmand } from './C0mmand';


interface Env {
  TWILIO_ACCOUNT_SID: string;
  TWILIO_AUTH_TOKEN: string;
}

export const findPhone: C0mmand = {
  name: 'Find Phone',
  id: 1,
  requiredEnv: [
    'TWILIO_ACCOUNT_SID',
    'TWILIO_AUTH_TOKEN'
  ],
  execute: async (env: Env) => {
    const { TWILIO_ACCOUNT_SID, TWILIO_AUTH_TOKEN } = env;

    const client = twilio(TWILIO_ACCOUNT_SID, TWILIO_AUTH_TOKEN);

    const twiml = new twilio.twiml.VoiceResponse();
    twiml.dial({}, '+447730333230');
    twiml.play('https://demo.twilio.com/docs/classic.mp3');

    const call = await client.calls.create({
        twiml: twiml.toString(),
        to: '+447730333230',
        from: '+443330164161'
      });

    return call.accountSid;
  }
}
