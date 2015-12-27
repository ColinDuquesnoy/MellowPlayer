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
#include "controllers/services.h"
#include "views/wizard_new_plugin.h"
#include "ui_wizard_new_plugin.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
WizardNewPlugin::WizardNewPlugin(QWidget *parent)
    : QWizard(parent), m_ui(new Ui::Wizard) {
  m_ui->setupUi(this);
  m_originalFinishedText = m_ui->labelFinished->text();

  connect(m_ui->btOpenPluginDir, &QPushButton::clicked,
          this, &WizardNewPlugin::onOpenPluginDirClicked);
}

//-------------------------------------
WizardNewPlugin::~WizardNewPlugin() {
    delete m_ui;
}

//-------------------------------------
bool WizardNewPlugin::validateCurrentPage()
{
    if(currentId() == int(Pages::Details)){
        QDir pluginsDir(getUserPluginsDirectory());
        if(!pluginsDir.exists())
            pluginsDir.mkpath(".");
        QString svName = m_ui->editSvName->text().toLower().split(" ")[0];
        QDir pluginDir(QFileInfo(pluginsDir, svName).absoluteFilePath());
        if(pluginDir.exists())
            return false;
        pluginDir.mkpath(".");
        m_pluginDir = pluginDir;
        createPlugin(pluginDir);
        m_ui->labelFinished->setText(m_originalFinishedText.arg(pluginDir.path()));
    }
    return true;
}

//-------------------------------------
void WizardNewPlugin::onOpenPluginDirClicked()
{
    QDesktopServices::openUrl(QUrl(m_pluginDir.path()));
}

//-------------------------------------
bool WizardNewPlugin::createNewPlugin(QWidget *parent)
{
    WizardNewPlugin wizard(parent);
    if(wizard.exec() == wizard.Accepted)
        return true;
    return false;
}

//-------------------------------------
void WizardNewPlugin::createPlugin(const QDir &pluginDir)
{
    createFile(pluginDir, "integration.js");
    createFile(pluginDir, "description.html");
    createFile(pluginDir, "logo.svg");
    createFile(pluginDir, "metadata.ini");
}

//-------------------------------------
void WizardNewPlugin::createFile(const QDir &pluginDir, const QString &filename) {
  QFile fin(QString(":/plugin_template/%1").arg(filename));
  if(!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Failed to read plugin file" << filename;
    return;
  }
  QTextStream in(&fin);
  QString text = in.readAll();
  fin.close();
  if(filename == "metadata.ini") {
      text = text.arg(m_ui->editAuthor->text(), m_ui->editAuthorUrl->text(),
                      m_ui->editSvName->text(), m_ui->editSvUrl->text());
  }
  QFile fout(QFileInfo(pluginDir, filename).absoluteFilePath());
  if(fout.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&fout);
      out << text;
  }
  fout.close();
}
