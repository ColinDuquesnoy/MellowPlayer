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
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include "controllers/services.h"
#include "views/mainwindow.h"
#include "views/dlgselectservice.h"
#include "ui_dlg_select_service.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
DlgSelectServices::DlgSelectServices(MainWindow *parent)
    : QDialog((QWidget *)parent), m_ui(new Ui::DialogSelectServices()),
      m_mainWindow(parent) {
  m_ui->setupUi(this);

  connect(m_ui->listWidget, SIGNAL(currentRowChanged(int)), this,
          SLOT(onCurrentRowChanged(int)));

  int row = 0;

  foreach (StreamingServicePlugin plugin, parent->services()->services()) {
    QListWidgetItem *item = new QListWidgetItem(m_ui->listWidget);
    item->setText(plugin.Name);
    item->setIcon(plugin.Icon);

    if (plugin.Name == parent->services()->currentService().Name)
      row = m_ui->listWidget->count() - 1;

    m_ui->listWidget->addItem(item);
  }

  m_ui->listWidget->setCurrentRow(row);
}

//--------------------------------------
DlgSelectServices::~DlgSelectServices() {
  delete m_ui;
}

//--------------------------------------
void DlgSelectServices::onCurrentRowChanged(int row) {
  QListWidgetItem *item = m_ui->listWidget->item(row);
  StreamingServicePlugin plugin =
      m_mainWindow->services()->getService(item->text());
  m_ui->textBrowser->setHtml(
      QObject::tr("<h1>%1</h1>"
                  "<h2>Description</h2>"
                  "%2"
                  "<h2>Service information</h2>"
                  "<p><strong>Maintainer: </strong><a href=%3>%4</a></p>"
                  "<p><strong>Version: </strong>%5</p>")
          .arg(plugin.Name)
          .arg(plugin.Description)
          .arg(plugin.AuthorWebSite)
          .arg(plugin.Author)
          .arg(plugin.Version));
}

//--------------------------------------
QString DlgSelectServices::selectService(MainWindow *parent) {
  DlgSelectServices dlg(parent);
  if (dlg.exec() == QDialog::Accepted) {
    QString serviceName = dlg.m_ui->listWidget->currentItem()->text();
    return serviceName;
  }
  return "";
}
