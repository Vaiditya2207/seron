"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.LocalStorage = exports.clearLocalStorage = exports.removeLocalStorageItem = exports.setLocalStorageItem = exports.getLocalStorageItem = exports.allLocalStorageItems = void 0;
const api_1 = require("@seron/api");
// We support deprecated local storage methods:
// https://developers.raycast.com/misc/migration/v1.28.0#storage
exports.allLocalStorageItems = api_1.LocalStorage.allItems;
exports.getLocalStorageItem = api_1.LocalStorage.getItem;
exports.setLocalStorageItem = api_1.LocalStorage.setItem;
exports.removeLocalStorageItem = api_1.LocalStorage.removeItem;
exports.clearLocalStorage = api_1.LocalStorage.clear;
var api_2 = require("@seron/api");
Object.defineProperty(exports, "LocalStorage", { enumerable: true, get: function () { return api_2.LocalStorage; } });
