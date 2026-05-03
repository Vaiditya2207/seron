import * as vicinae from '@seron/api';

// older versions of the Raycast API had ActionPanel.Item
export const ActionPanel = Object.assign(vicinae.ActionPanel, {
	Item: vicinae.Action
})
