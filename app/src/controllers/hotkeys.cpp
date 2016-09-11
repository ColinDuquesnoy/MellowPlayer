//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QAction>
#include <qxtglobalshortcut.h>
#include "controllers/hotkeys.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
HotkeysController::HotkeysController(MainWindow *parent)
    : BaseController("hotkeys", parent) {
  QAction *actions[] = {
      parent->ui()->actionPlayPause, parent->ui()->actionNext,
      parent->ui()->actionPrevious, parent->ui()->actionAdd_to_favorites,
  };
  qDebug() << "Hotkeys: Setting up Qxt global shortcuts";
  for (int i = 0; i < 4; ++i) {
    QAction *action = actions[i];
    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(this);
    shortcut->setObjectName(action->objectName());
    if (shortcut->setShortcut(action->shortcut()))
      qDebug() << "Global shortcut registered: " << action->shortcut()
               << "\t: " << action->objectName();
    connect(shortcut, SIGNAL(activated()), action, SLOT(trigger()));
    m_shortcuts.append(shortcut);
  }
#ifdef Q_OS_WIN
  QAction *mediaActions[] = {
      parent->ui()->actionPlayPause, parent->ui()->actionPlayPause,
      parent->ui()->actionNext, parent->ui()->actionPrevious};
  int shortcuts[] = {Qt::Key_MediaPlay, Qt::Key_MediaStop, Qt::Key_MediaNext,
                     Qt::Key_MediaPrevious};
  QStringList names;
  names << "MediaPlay"
        << "MediaStop"
        << "MediaNext"
        << "MediaPrevious";
  qDebug() << "Hotkeys: Setting up Media shortcuts";
  for (int i = 0; i < names.count(); ++i) {
    QAction *action = mediaActions[i];
    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(this);
    shortcut->setObjectName(names[i]);
    if (shortcut->setShortcut(shortcuts[i]))
      qDebug() << "Media shortcut registered: " << names[i];
    connect(shortcut, SIGNAL(activated()), action, SLOT(trigger()));
    m_shortcuts.append(shortcut);
  }
#endif
}

//-------------------------------------
void HotkeysController::applyPreferences() {
  QAction *actions[] = {
      m_mainWindow->ui()->actionPlayPause, m_mainWindow->ui()->actionNext,
      m_mainWindow->ui()->actionPrevious,
      m_mainWindow->ui()->actionAdd_to_favorites,
  };
  qDebug() << "Hotkeys : updating Qxt global shortcuts";
  for (int i = 0; i < 4; ++i) {
    QAction *action = actions[i];
    QxtGlobalShortcut *shortcut = m_shortcuts[i];
    if (shortcut->setShortcut(action->shortcut()))
      qDebug() << "Global shortcut updated: " << action->shortcut() << ":"
               << action->objectName();
  }
}
