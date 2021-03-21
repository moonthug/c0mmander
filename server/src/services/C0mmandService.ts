import { C0mmand, Id } from './c0mmands/C0mmand';
import { printShoppingList } from './c0mmands/printShoppingList';

export class C0mmandService {
  private readonly _c0mmands: C0mmand[];

  constructor() {
    this._c0mmands = [
      printShoppingList
    ];

    this._c0mmands.forEach(c0mmand => {
      if (!c0mmand.requiredEnv.every(key => Object.keys(process.env).includes(key))) {
        throw new Error(`Environment variables missing for c0mmand: ${c0mmand.name}: ${c0mmand.requiredEnv}`);
      }
    })
  }

  public getC0mmands() {
    return this._c0mmands.map(c0mmand => {
      return {
        id: c0mmand.id,
        name: c0mmand.name
      }
    })
  }

  public async executeCommand(id: Id) {
    const c0mmand = this._c0mmands.find(command => command.id === id);

    if (!c0mmand) {
      throw new Error('Command not found!');
    }

    return await c0mmand.execute(process.env);
  }
}
