import * as seron from '@seron/api';
import * as raycast from '@raycast/api';

export namespace Clipboard {
	export const copy: typeof raycast.Clipboard.copy = (content, opts) => {
		return seron.Clipboard.copy(content, {
			concealed: opts?.concealed || opts?.transient,
			...opts
		});
	}

	export const paste: typeof raycast.Clipboard.paste = seron.Clipboard.paste;
	export const read: typeof raycast.Clipboard.read = seron.Clipboard.read;
	export const readText: typeof raycast.Clipboard.readText = seron.Clipboard.readText;
	export const clear: typeof raycast.Clipboard.clear = seron.Clipboard.clear;
};

