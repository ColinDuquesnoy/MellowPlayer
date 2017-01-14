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

#ifndef HOTKEYSCONTROLLER_H
#define HOTKEYSCONTROLLER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include "controllers/base.h"

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class MainWindow;
class QxtGlobalShortcut;

class HotkeysController : public BaseController {
  Q_OBJECT
public:
  explicit HotkeysController(MainWindow *parent = 0);
  void applyPreferences() override;

signals:

public slots:

private:
  QList<QxtGlobalShortcut *> m_shortcuts;
};

#endif // HOTKEYSCONTROLLER_H
