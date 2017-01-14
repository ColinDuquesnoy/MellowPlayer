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

#ifndef DLGSELECTSERVICE_H
#define DLGSELECTSERVICE_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QDialog>
#include <QListWidgetItem>

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
namespace Ui {
class DialogSelectServices;
}
class MainWindow;

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
/*!
 * \brief The DlgSelectServices class implement the streaming service selection
 * dialog.
 */
class DlgSelectServices : public QDialog {
  Q_OBJECT

public:
  explicit DlgSelectServices(MainWindow *parent = NULL);
  ~DlgSelectServices();

  /*!
   * \brief Convenience function for selecting a streaming service.
   *
   * \param parent Parent widget of the DialogCode
   *
   * \return Name of the selected service. Empty string if the dialog
   * was cancelled.
   */
  static QString selectService(MainWindow *parent);

private slots:
  void onCurrentRowChanged(int row);

private:
  Ui::DialogSelectServices *m_ui;
  MainWindow *m_mainWindow;
};

#endif // DLGSELECTSERVICE_H
