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
#include "views/hoverable_button.h"
#include <QApplication>

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
HoverableButton::HoverableButton(QWidget *parent) : QPushButton(parent) {
  setMouseTracking(true);
}

void HoverableButton::setDisplayText(const QString &displayText) {
  m_displayText = displayText;
}

//-------------------------------------
void HoverableButton::enterEvent(QEvent *event) {
  Q_UNUSED(event);
  qApp->setOverrideCursor(Qt::PointingHandCursor);
  emit mouseHoverEvent(m_displayText);
}

//-------------------------------------
void HoverableButton::leaveEvent(QEvent *event) {
  Q_UNUSED(event);
  qApp->restoreOverrideCursor();
  emit mouseHoverEvent("");
}
