import { Todoist } from 'todoist';
import axios from 'axios';
import { C0mmand } from './C0mmand';


interface Env {
  TP_SERVER_URL: string;
}

export const dummy: C0mmand = {
  name: 'Dummy Command',
  id: 2,
  requiredEnv: [],
  execute: async (env: Env) => {
    const { TP_SERVER_URL } = env;

    const instructions = [
      'style "normal"',
      'align "lt"',
      'size "4" "4"',
      'text "Dummy!"',
      'text ""',
      'text ""',
      'text ""',
      'text ""',
      'text ""',
      'cut'
    ];

    try {
      const { data } = await axios(
        `${TP_SERVER_URL}/job`,
        {
          headers: {
            'content-type': 'text/plain'
          },
          data: instructions.join('\n'),
          method: 'POST'
        }
      );
      return data;
    } catch (e) {
      console.log('Print fail');
    }
  }
}
