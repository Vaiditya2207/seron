import { spawnSync } from "node:child_process";

export type SeronClientOptions = {
	binaryPath: string;
};

export class SeronClient {
	constructor(
		private readonly options: SeronClientOptions = { binaryPath: "seron" },
	) {}

	ping() {
		return this.invoke("/ping");
	}

	refreshDevSession(extensionId: string) {
		return this.invoke(`/api/extensions/develop/refresh?id=${extensionId}`);
	}

	startDevSession(extensionId: string) {
		return this.invoke(`/api/extensions/develop/start?id=${extensionId}`);
	}

	stopDevSession(extensionId: string) {
		return this.invoke(`/api/extensions/develop/stop?id=${extensionId}`);
	}

	private invoke(endpoint: string): Error | null {
		if (endpoint.startsWith("/")) {
			endpoint = endpoint.slice(1);
		}

		const url = `seron://${endpoint}`;
		const result = spawnSync(this.options.binaryPath, [url]);

		if (result.error) return result.error;

		return result.status === 0 ? null : new Error(result.stderr.toString());
	}
}
