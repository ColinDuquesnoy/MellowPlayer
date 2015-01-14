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
#include <QAction>
#include <qglobal.h>
#include "hotkeys.h"
#ifdef __kde_support__
    #include "KGlobalAccel"
#else
    #include "qxtglobalshortcut.h"
#endif

//---------------------------------------------------------
const PluginMetaData &HotkeysPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Hotkeys";
    meta.author = "Colin Duquesnoy";
    meta.website = "https://github.com/ColinDuquesnoy/MellowPlayer";
    meta.version = "1.0";
    meta.description =tr("Adds support for global shortcuts.");
    return meta;
}

//---------------------------------------------------------
void HotkeysPlugin::setup()
{
    QString names[] = {"actionPlayPause", "actionStop", "actionNext",
                       "actionPrevious"};
#ifdef __kde_support__
    qDebug() << "Hotkeys Plugin: Setting up KGlobalAccel shortcuts";
    for(int i = 0; i < 4; ++i){
        QAction* action = Services::action(names[i]);
        if(!action)
            continue;
        if(KGlobalAccel::setGlobalShortcut(action, action->shortcut()))
            qDebug() << "Global shortcut registered: "
                     << action->objectName() << "\t: " << action->shortcut();
    }
#else
    qDebug() << "Hotkeys Plugin: Setting up Qxt global shortcuts";
    for(int i = 0; i < 4; ++i){
        QAction* action = Services::action(names[i]);
        if(!action)
            continue;
        QxtGlobalShortcut* shortcut = new QxtGlobalShortcut();
        shortcut->setObjectName(action->objectName());
        if(shortcut->setShortcut(action->shortcut()))
            qDebug() << "Global shortcut registered: "
                     << shortcut->objectName() << "\t: " << action->shortcut();
        connect(shortcut, SIGNAL(activated()), action, SLOT(trigger()));
        this->shortcuts.append(shortcut);
    }
#endif
}

//---------------------------------------------------------
void HotkeysPlugin::teardown()
{

}

//---------------------------------------------------------
QString HotkeysPlugin::description() const
{
    return tr("Provides support hotkeys");
}

//---------------------------------------------------------
QWidget *HotkeysPlugin::settingsWidget() const
{
    return NULL;
}

//---------------------------------------------------------
void HotkeysPlugin::resetSettings(QWidget *widget) const
{
    Q_ASSERT(widget == NULL);
}

//---------------------------------------------------------
void HotkeysPlugin::restoreDefaultSettings(QWidget *widget) const
{
    Q_ASSERT(widget == NULL);
}

//---------------------------------------------------------
void HotkeysPlugin::applySettings(QWidget *widget) const
{
    Q_ASSERT(widget == NULL);
}

#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2( hotkeys, HotkeysPlugin )
#endif
