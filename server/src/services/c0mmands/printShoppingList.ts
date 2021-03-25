import { Todoist } from 'todoist';
import axios from 'axios';
import { C0mmand } from './C0mmand';


interface Env {
  TODOIST_API_KEY: string;
  TP_SERVER_URL: string;
}

export const printShoppingList: C0mmand = {
  name: 'Print Shopping List',
  id: 0,
  requiredEnv: [
    'TODOIST_API_KEY',
    'TP_SERVER_URL'
  ],
  execute: async (env: Env) => {
    const { TODOIST_API_KEY, TP_SERVER_URL } = env;

    let items: any[];

    try {
      const todoist = Todoist(TODOIST_API_KEY);
      await todoist.sync();
      items = todoist.items.get();
    } catch (e) {
      console.log('Todoist fail');
    }

    const list = items.map(item => {
      return [
        'size "1" "1"',
        `text "[ ] ${item.content}"`,
      ].join('\n');
    });

    const instructions = [
      'style "normal"',
      'align "lt"',
      'size "4" "4"',
      'text "Shopping List"',
      'text ""',
      'text ""',
      'size "1" "1"',
      ...list,
      'text ""',
      'text ""',
      'text ""',
      'text ""',
      'text ""',
      'cut'
    ].join('\n');

    try {
      const { data } = await axios(
        `${TP_SERVER_URL}/job`,
        {
          headers: {
            'content-type': 'text/plain'
          },
          data: instructions,
          method: 'POST'
        }
      );
      return data;
    } catch (e) {
      console.log('Print fail');
    }
  }
}
