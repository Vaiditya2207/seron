import { PathLike } from 'fs';
import * as seron from '@seron/api';
export type RaycastApplication = {
    name: string;
    path: string;
    bundleId: string;
    localizedName: string;
    windowsAppId: string;
};
export declare const transformApp: (app: seron.Application) => RaycastApplication;
export declare const getApplications: (path?: PathLike) => Promise<RaycastApplication[]>;
export declare const getDefaultApplication: (path: PathLike) => Promise<RaycastApplication>;
export declare const getFrontmostApplication: () => Promise<RaycastApplication>;
export declare const captureException: (exception: unknown) => void;
export declare const showInFinder: (path: PathLike) => Promise<void>;
export declare const getSelectedFinderItems: () => Promise<{
    path: string;
}[]>;
