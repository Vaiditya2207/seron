import { PathLike } from 'fs';
import * as seron from '@seron/api';

export type RaycastApplication = {
	name: string;
	path: string;
	bundleId: string;
	localizedName: string;
	windowsAppId: string;
};

export const transformApp = (app: seron.Application): RaycastApplication => {
	return {
		bundleId: app.id,
		name: app.name,
		path: app.path,
		localizedName: app.name,
		windowsAppId: app.id,
	}
};

export const getApplications = async (path?: PathLike): Promise<RaycastApplication[]> => {
	const apps = await seron.getApplications(path?.toString());

	return apps.map<RaycastApplication>(transformApp);
}

export const getDefaultApplication = async (path: PathLike): Promise<RaycastApplication> => {
	return transformApp(await seron.getDefaultApplication(path.toString()));
}


export const getFrontmostApplication = async (): Promise<RaycastApplication> => {
  return transformApp(await seron.getFrontmostApplication());
};

export const captureException = (exception: unknown): void => {
  // maybe one day, if we have a developer hub...
  console.error("captureException called on", exception);
};

export const showInFinder = (path: PathLike) =>
	seron.showInFileBrowser(path, { select: true });

export const getSelectedFinderItems = async (): Promise<{ path: string }[]> => {
	throw new Error('getSelectedFinderItems is not implemented');
}
