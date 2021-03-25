declare module "trello" {
  interface Card {
    id: string;
    name: string;
    idChecklists: string[];
  }

  interface CheckItem {
    id: string;
    due: Date | null;
    name: string;
    state: 'complete' | 'incomplete';
  }

  interface Checklist {
    id: string;
    name: string;
    checkItems: CheckItem[]
  }

  type getCardsOnListCallback = (cards: Card[]) => void;
  type getChecklistsOnCardCallback = (checklists: Checklist[]) => void;

  export default class Trello {

    constructor(key: string, token: string);

    getCardsOnList(listId: string): Promise<Card[]>;
    getCardsOnList(listId: string, callback: getCardsOnListCallback): void;

    getChecklistsOnCard(listId: string): Promise<Checklist[]>;
    getChecklistsOnCard(listId: string, callback: getChecklistsOnCardCallback): void;
  }
}
