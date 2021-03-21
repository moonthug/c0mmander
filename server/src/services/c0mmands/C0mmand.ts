export type Id = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11;

export interface C0mmand {
  name: string;
  id: Id;
  requiredEnv: string[];
  execute: (env: unknown) => any;
}
