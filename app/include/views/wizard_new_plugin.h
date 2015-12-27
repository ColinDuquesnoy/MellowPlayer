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

#ifndef WIZARD_NEW_PLUGIN_H
#define WIZARD_NEW_PLUGIN_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QtWidgets>

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
namespace Ui {
class Wizard;
}

//---------------------------------------------------------
// Definitions
//---------------------------------------------------------
#define PAGE_HOME 0
#define PAGE_WEB 1

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
//! Implements the main window of the application.
class WizardNewPlugin : public QWizard {
  Q_OBJECT
  enum class Pages {
      Intro = 0,
      Details = 1,
      Finished = 2
  };

public:
  explicit WizardNewPlugin(QWidget *parent = 0);
  ~WizardNewPlugin();
  static bool createNewPlugin(QWidget* parent);

protected:
  bool validateCurrentPage();

private slots:
  void onOpenPluginDirClicked();

private:
  void createPlugin(const QDir& pluginDir);
  void createFile(const QDir& pluginDir, const QString& filename);
  Ui::Wizard* m_ui;
  QString m_originalFinishedText;
  QDir m_pluginDir;
};

#endif // WIZARD_NEW_PLUGIN_H
