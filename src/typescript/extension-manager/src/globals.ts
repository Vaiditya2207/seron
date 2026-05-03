import type { Environment } from "@seron/api";
import type { Client } from "./proto/api";

type VicinaGlobal = {
	client: Client;
	environ: Environment;
	preferences: any;
	navigationContext: any;
};

type Global = typeof globalThis & {
	seron: VicinaGlobal;
};

(globalThis as Global).seron = {
	environ: {} as any,
	preferences: {} as any,
	client: {} as any,
	navigationContext: undefined as any,
};

export const globalState = (globalThis as Global).seron;
