/**
 * Raycast compatible entrypoint.
 * We mostly re-export @seron/api stuff but it is expected that @seron/api will
 * become more and more independent overtime, not strictly following what Raycast does
 * but remaining compatible with it.
 */
export { useNavigation, Toast, showToast, ImageLike, Image, Keyboard, KeyModifier, Icon, environment, Environment, Cache, Color, ColorLike, getPreferenceValues, confirmAlert, Alert, open, showInFileBrowser, closeMainWindow, showHUD, clearSearchBar, getSelectedText, popToRoot, PopToRootType, updateCommandMetadata, openCommandPreferences, openExtensionPreferences, LaunchType, AI, OAuth, List, Grid, Form, Detail, Action } from '@seron/api';
export { getFrontmostApplication, getApplications, getDefaultApplication, showInFinder, captureException, } from "./system.js";
export { Clipboard } from './clipboard.js';
export { ActionPanel } from "./components/action-panel.js";
export { randomId } from './utils.js';
export * from "./local-storage.js";
export { WindowManagement } from './window-management.js';
