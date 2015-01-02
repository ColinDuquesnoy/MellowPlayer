//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------
#include <QtWidgets>
#include "hotkeys.h"

#ifdef __kde_support__
    #include "KGlobalAccel"
#else
    #include "qxtglobalshortcut.h"
#endif

#define DEFAULT_SHORTCUT_PLAY       "Media Play"
#define DEFAULT_SHORTCUT_STOP       "Media Stop"
#define DEFAULT_SHORTCUT_NEXT       "Media Next"
#define DEFAULT_SHORTCUT_PREVIOUS   "Media Previous"


void HotkeysPlugin::setup()
{
    QString shortcuts[] = {DEFAULT_SHORTCUT_PLAY, DEFAULT_SHORTCUT_STOP,
                           DEFAULT_SHORTCUT_NEXT, DEFAULT_SHORTCUT_PREVIOUS};
    QString names[] = {"actionPlayPause", "actionStop", "actionNext",
                       "actionPrevious"};

#ifdef __kde_support__
    qDebug() << "Hotkeys Plugin: Setting up KGlobalAccel shortcuts";
    for(int i = 0; i < 4; ++i){
        KGlobalAccel::setGlobalShortcut(Services::action(names[i]),
                                        QKeySequence(shortcuts[i]));
    }
#else
    qDebug() << "Hotkeys Plugin: Setting up Qxt global shortcuts";
    for(int i = 0; i < 4; ++i){
        QAction* action = Services::action(names[i]);
        if(!action)
            continue;
        QxtGlobalShortcut* shortcut = new QxtGlobalShortcut();
        shortcut->setObjectName(names[i].remove("action"));
        if(shortcut->setShortcut(QKeySequence(shortcuts[i])))
            qDebug() << "Global shortcut registered: "
                     << shortcut->objectName() << ": " << shortcuts[i];
        connect(shortcut, &QxtGlobalShortcut::activated,
                action, &QAction::trigger);
        this->shortcuts.append(shortcut);
    }
#endif
}

void HotkeysPlugin::teardown()
{

}

QWidget *HotkeysPlugin::settingsWidget()
{
#ifdef __kde_support__
    // no settings when built with kde support, hotkeys settings are configured
    // using K System Settings -> shortcuts -> Global Shortcuts.
    return NULL;
#endif
// todo
return NULL;
}
