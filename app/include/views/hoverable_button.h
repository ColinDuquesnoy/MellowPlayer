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

#ifndef HOVERABLE_BUTTON_H
#define HOVERABLE_BUTTON_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QPushButton>

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
/*!
 * \brief Extends QPushButton to emit some signals related to mouse hover.
 *
 * This class is used to display a text in an extern QLabel.
 */
class HoverableButton : public QPushButton {
  Q_OBJECT
public:
  explicit HoverableButton(QWidget *parent = NULL);

  /*!
   * \brief Sets the display text associated with this button.
   *
   * \param displayText Text to display when mouseEnter the widget
   */
  void setDisplayText(const QString &displayText);

signals:
  /**
   * @brief Signal emitted when the mouse enter or leave the button.
   * @param displayText Associated display text or empty string depending of
   * whether the mouse entered or leaved the button.
   */
  void mouseHoverEvent(const QString &displayText);

protected:
  virtual void enterEvent(QEvent *event);
  virtual void leaveEvent(QEvent *event);

private:
  QString m_displayText;
};

#endif // HOVERABLE_BUTTON_H
