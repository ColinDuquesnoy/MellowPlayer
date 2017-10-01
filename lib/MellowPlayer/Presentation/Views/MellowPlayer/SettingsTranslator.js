function translateName(name) {
    var translations = {
        'Confirm application exit': qsTr('Confirm application exit'),
        'Close application to system tray': qsTr('Close application to system tray'),
        'Show system tray icon': qsTr('Show system tray icon'),
        'Check for updates': qsTr('Check for updates'),
        'Update channel': qsTr('Update channel'),
        'Theme': qsTr('Theme'),
        'Accent': qsTr('Accent'),
        'Background': qsTr('Background'),
        'Foreground': qsTr('Foreground'),
        'Primary Background': qsTr('Primary Background'),
        'Primary Foreground': qsTr('Primary Foreground'),
        'Secondary Background': qsTr('Secondary Background'),
        'Secondary Foreground': qsTr('Secondary Foreground'),
        'Enable notifications': qsTr('Enable notifications'),
        'Display a notification when a new song starts playing': qsTr('Display a notification when a new song starts playing'),
        'Display a notification when player has paused': qsTr('Display a notification when player has paused'),
        'Display a notification when player has resumed': qsTr('Display a notification when player has resumed'),
        'Play / Pause': qsTr('Play / Pause'),
        'Next': qsTr('Next'),
        'Previous': qsTr('Previous'),
        'Add to favorites': qsTr('Add to favorites'),
        'Restore window': qsTr('Restore window'),
        'Reload page': qsTr('Reload page'),
        'Select service': qsTr('Select service'),
        'Next service': qsTr('Next service'),
        'Previous service': qsTr('Previous service'),
        'Toggle notifications': qsTr('Toggle notifications'),
        'Listening history': qsTr('Listening history'),
        'Settings': qsTr('Settings'),
        'Create Plugin': qsTr('Create Plugin'),
        'Report Issue': qsTr('Report Issue'),
        'Check for update': qsTr('Check for update'),
        'About': qsTr('About'),
        'Quit': qsTr('Quit'),
        'Enable listening history': qsTr('Enable listening history'),
        'Listening history limit': qsTr('Listening history limit'),
        'User agent': qsTr('User agent')
    };

    return translations[name];
}

function translateToolTip(toolTip) {
    var translations = {
        'Enable this option to get a confirmation message when you leave MellowPlayer.': qsTr('Enable this option to get a confirmation message when you leave MellowPlayer.'),
        'Enable this option to close the application in the system tray and continue listening to your musing in background.': qsTr('Enable this option to close the application in the system tray and continue listening to your musing in background.'),
        'Disable this option to hide the system tray icon': qsTr('Disable this option to hide the system tray icon'),
        'Automatically check for updates': qsTr('Automatically check for updates'),
        'Choose which update channel to use': qsTr('Choose which update channel to use'),
        'Application theme': qsTr('Application theme'),
        'Change material accent color': qsTr('Change material accent color'),
        'Change material background color': qsTr('Change material background color'),
        'Change material foreground color': qsTr('Change material foreground color'),
        'Change material primary background color': qsTr('Change material primary background color'),
        'Change material primary foreground color': qsTr('Change material primary foreground color'),
        'Change material secondary background color': qsTr('Change material secondary background color'),
        'Change material secondary foreground color': qsTr('Change material secondary foreground color'),
        'Enable or disable notifications': qsTr('Enable or disable notifications'),
        'Enabled/Disable displaying a notification when a new song starts playing': qsTr('Enabled/Disable displaying a notification when a new song starts playing'),
        'Enabled/Disable displaying a notification when the player has paused': qsTr('Enabled/Disable displaying a notification when the player has paused'),
        'Enabled/Disable displaying a notification when the player has resumed': qsTr('Enabled/Disable displaying a notification when the player has resumed'),
        'Global hotkey that plays or pauses the current player.': qsTr('Global hotkey that plays or pauses the current player.'),
        'Global hotkey that skips to the next song.': qsTr('Global hotkey that skips to the next song.'),
        'Global hotkey that skips to the previous song.': qsTr('Global hotkey that skips to the previous song.'),
        'Global hotkey that adds or removes the current song to or from your favorites.': qsTr('Global hotkey that adds or removes the current song to or from your favorites.'),
        'Global hotkey that restore the main window.': qsTr('Global hotkey that restore the main window.'),
        'Reload current web page.': qsTr('Reload current web page.'),
        'Show service selection page.': qsTr('Show service selection page.'),
        'Switch to the next open service.': qsTr('Switch to the next open service.'),
        'Switch to the previous open service.': qsTr('Switch to the previous open service.'),
        'Quickly enable or disable notifications': qsTr('Quickly enable or disable notifications'),
        'Show or hide listening history': qsTr('Show or hide listening history'),
        'Show settings page': qsTr('Show settings page'),
        'Show the plugin creation wizard': qsTr('Show the plugin creation wizard'),
        'Create an issue on github': qsTr('Create an issue on github'),
        'Check for update': qsTr('Check for update'),
        'Show about page.': qsTr('Show about page.'),
        'Quit the application.': qsTr('Quit the application.'),
        'Enable listening history to keep track of the songs you listened to.': qsTr('Enable listening history to keep track of the songs you listened to.'),
        'Specifies the limit of the listening history': qsTr('Specifies the limit of the listening history'),
        'Specifies the user agent string used for http requests': qsTr('Specifies the user agent string used for http requests')
    };

    return translations[toolTip];
}

function translateCategory(category) {
    var translations = {
        "Services": qsTr("Services"),
        "Cache": qsTr("Cache"),
        'General': qsTr('General'),
        'Appearance': qsTr('Appearance'),
        'Notifications': qsTr('Notifications'),
        'Shortcuts': qsTr('Shortcuts'),
        'Privacy': qsTr('Privacy')
    };

    return translations[category];
}
