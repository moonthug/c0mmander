import * as fs from 'fs';
import * as path from 'path';
import Trello from 'trello';
import handlbars from 'handlebars'
import { C0mmand } from './C0mmand';
import axios from 'axios';

interface Env {
  TRELLO_APP_KEY: string;
  TRELLO_APP_TOKEN: string;
  TRELLO_TODO_LIST_ID: string;
  TRELLO_BUY_LIST_ID: string;
  TP_SERVER_URL: string;
}

const template = handlbars.compile(
  fs.readFileSync(path.join(__dirname, 'templates', 't0d0.hbs'))
    .toString('utf-8')
);

function nth(d: number) {
  if (d > 3 && d < 21) return 'th';
  switch (d % 10) {
    case 1:  return 'st';
    case 2:  return 'nd';
    case 3:  return 'rd';
    default: return 'th';
  }
}

function getNiceDate() {
  const days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];
  const months = ['January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December'
  ];
  const d = new Date();
  return `${days[d.getDay()]} ${d.getDate()}${nth(d.getDate())} of ${months[d.getMonth()]}`;
}

export const printT0d0s: C0mmand = {
  name: 'Print t0d0s',
  id: 2,
  requiredEnv: [
    'TRELLO_APP_KEY',
    'TRELLO_APP_TOKEN',
    'TRELLO_TODO_LIST_ID',
    'TRELLO_BUY_LIST_ID',
    'TP_SERVER_URL'
  ],
  execute: async (env: Env) => {
    const { TRELLO_APP_KEY, TRELLO_APP_TOKEN, TRELLO_TODO_LIST_ID, TRELLO_BUY_LIST_ID, TP_SERVER_URL } = env;

    const client = new Trello(TRELLO_APP_KEY, TRELLO_APP_TOKEN);

    const doStuffCards = await client.getCardsOnList('5f7723264eca846e30d3bb41');
    const cardsWithChecklists = await Promise.all(
      doStuffCards.map(async (card) => {
        return {
          ...card,
          checklists: card.idChecklists.length
            ? (await client.getChecklistsOnCard(card.id))
              .map(checklist => {
                checklist.checkItems = checklist.checkItems
                  .map(checkItem => {
                    return {
                      isComplete: (checkItem.state === 'complete'),
                      ...checkItem
                    }
                  })
                return checklist;
              })
            : undefined
        }
      })
    );
    const onHoldCards = await client.getCardsOnList(TRELLO_TODO_LIST_ID);
    const buyStuffCards = await client.getCardsOnList(TRELLO_BUY_LIST_ID);

    const instructions = template({
      date: getNiceDate(),
      doStuffCards: cardsWithChecklists,
      onHoldCards,
      buyStuffCards,
    })
      .split('\n')
      .map(line => line.trim())
      .filter(line => line !== '')
      .join('\n');

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
      console.error(e);
      console.log('Print fail');
    }
  }
}
