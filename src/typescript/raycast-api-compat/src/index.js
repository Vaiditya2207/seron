"use strict";
/**
 * Raycast compatible entrypoint.
 * We mostly re-export @seron/api stuff but it is expected that @seron/api will
 * become more and more independent overtime, not strictly following what Raycast does
 * but remaining compatible with it.
 */
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __exportStar = (this && this.__exportStar) || function(m, exports) {
    for (var p in m) if (p !== "default" && !Object.prototype.hasOwnProperty.call(exports, p)) __createBinding(exports, m, p);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.WindowManagement = exports.randomId = exports.ActionPanel = exports.Clipboard = exports.captureException = exports.showInFinder = exports.getDefaultApplication = exports.getApplications = exports.getFrontmostApplication = exports.Action = exports.Detail = exports.Form = exports.Grid = exports.List = exports.OAuth = exports.AI = exports.LaunchType = exports.openExtensionPreferences = exports.openCommandPreferences = exports.updateCommandMetadata = exports.PopToRootType = exports.popToRoot = exports.getSelectedText = exports.clearSearchBar = exports.showHUD = exports.closeMainWindow = exports.showInFileBrowser = exports.Alert = exports.confirmAlert = exports.getPreferenceValues = exports.Color = exports.Cache = exports.environment = exports.Icon = exports.Keyboard = exports.Image = exports.showToast = exports.Toast = exports.useNavigation = void 0;
var api_1 = require("@seron/api");
Object.defineProperty(exports, "useNavigation", { enumerable: true, get: function () { return api_1.useNavigation; } });
Object.defineProperty(exports, "Toast", { enumerable: true, get: function () { return api_1.Toast; } });
Object.defineProperty(exports, "showToast", { enumerable: true, get: function () { return api_1.showToast; } });
Object.defineProperty(exports, "Image", { enumerable: true, get: function () { return api_1.Image; } });
Object.defineProperty(exports, "Keyboard", { enumerable: true, get: function () { return api_1.Keyboard; } });
Object.defineProperty(exports, "Icon", { enumerable: true, get: function () { return api_1.Icon; } });
Object.defineProperty(exports, "environment", { enumerable: true, get: function () { return api_1.environment; } });
Object.defineProperty(exports, "Cache", { enumerable: true, get: function () { return api_1.Cache; } });
Object.defineProperty(exports, "Color", { enumerable: true, get: function () { return api_1.Color; } });
Object.defineProperty(exports, "getPreferenceValues", { enumerable: true, get: function () { return api_1.getPreferenceValues; } });
Object.defineProperty(exports, "confirmAlert", { enumerable: true, get: function () { return api_1.confirmAlert; } });
Object.defineProperty(exports, "Alert", { enumerable: true, get: function () { return api_1.Alert; } });
Object.defineProperty(exports, "open", { enumerable: true, get: function () { return api_1.open; } });
Object.defineProperty(exports, "showInFileBrowser", { enumerable: true, get: function () { return api_1.showInFileBrowser; } });
Object.defineProperty(exports, "closeMainWindow", { enumerable: true, get: function () { return api_1.closeMainWindow; } });
Object.defineProperty(exports, "showHUD", { enumerable: true, get: function () { return api_1.showHUD; } });
Object.defineProperty(exports, "clearSearchBar", { enumerable: true, get: function () { return api_1.clearSearchBar; } });
Object.defineProperty(exports, "getSelectedText", { enumerable: true, get: function () { return api_1.getSelectedText; } });
Object.defineProperty(exports, "popToRoot", { enumerable: true, get: function () { return api_1.popToRoot; } });
Object.defineProperty(exports, "PopToRootType", { enumerable: true, get: function () { return api_1.PopToRootType; } });
Object.defineProperty(exports, "updateCommandMetadata", { enumerable: true, get: function () { return api_1.updateCommandMetadata; } });
Object.defineProperty(exports, "openCommandPreferences", { enumerable: true, get: function () { return api_1.openCommandPreferences; } });
Object.defineProperty(exports, "openExtensionPreferences", { enumerable: true, get: function () { return api_1.openExtensionPreferences; } });
Object.defineProperty(exports, "LaunchType", { enumerable: true, get: function () { return api_1.LaunchType; } });
Object.defineProperty(exports, "AI", { enumerable: true, get: function () { return api_1.AI; } });
Object.defineProperty(exports, "OAuth", { enumerable: true, get: function () { return api_1.OAuth; } });
Object.defineProperty(exports, "List", { enumerable: true, get: function () { return api_1.List; } });
Object.defineProperty(exports, "Grid", { enumerable: true, get: function () { return api_1.Grid; } });
Object.defineProperty(exports, "Form", { enumerable: true, get: function () { return api_1.Form; } });
Object.defineProperty(exports, "Detail", { enumerable: true, get: function () { return api_1.Detail; } });
Object.defineProperty(exports, "Action", { enumerable: true, get: function () { return api_1.Action; } });
var system_js_1 = require("./system.js");
Object.defineProperty(exports, "getFrontmostApplication", { enumerable: true, get: function () { return system_js_1.getFrontmostApplication; } });
Object.defineProperty(exports, "getApplications", { enumerable: true, get: function () { return system_js_1.getApplications; } });
Object.defineProperty(exports, "getDefaultApplication", { enumerable: true, get: function () { return system_js_1.getDefaultApplication; } });
Object.defineProperty(exports, "showInFinder", { enumerable: true, get: function () { return system_js_1.showInFinder; } });
Object.defineProperty(exports, "captureException", { enumerable: true, get: function () { return system_js_1.captureException; } });
var clipboard_js_1 = require("./clipboard.js");
Object.defineProperty(exports, "Clipboard", { enumerable: true, get: function () { return clipboard_js_1.Clipboard; } });
var action_panel_js_1 = require("./components/action-panel.js");
Object.defineProperty(exports, "ActionPanel", { enumerable: true, get: function () { return action_panel_js_1.ActionPanel; } });
var utils_js_1 = require("./utils.js");
Object.defineProperty(exports, "randomId", { enumerable: true, get: function () { return utils_js_1.randomId; } });
__exportStar(require("./local-storage.js"), exports);
var window_management_js_1 = require("./window-management.js");
Object.defineProperty(exports, "WindowManagement", { enumerable: true, get: function () { return window_management_js_1.WindowManagement; } });
