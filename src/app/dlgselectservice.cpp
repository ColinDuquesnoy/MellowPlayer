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

#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <mellowplayer.h>
#include "dlgselectservice.h"
#include "ui_dlg_select_service.h"

bool cmp(const IStreamingService* a,
                    const IStreamingService* b)
{
    return a->metaData().name < b->metaData().name;
}


//---------------------------------------------------------
DlgSelectServices::DlgSelectServices(QWidget *parent):
    QDialog(parent),
    m_ui(new Ui::DialogSelectServices())
{
    m_ui->setupUi(this);

    int row = 0;
    QString activeService = QSettings().value("service", "").toString();
    int i = 0;
    StreamingServicesList plugins = Services::streamingServices()->plugins();
    qSort(plugins.begin(), plugins.end(), cmp);
    foreach(IStreamingService* plugin, plugins){
        QListWidgetItem* item = new QListWidgetItem(m_ui->listWidget);
        item->setText(plugin->metaData().name);
        item->setIcon(plugin->metaData().icon);
        m_ui->listWidget->addItem(item);

        if(plugin->metaData().name == activeService)
            row = i;

        ++i;
    }

    connect(m_ui->listWidget, SIGNAL(currentRowChanged(int)),
            this, SLOT(onCurrentRowChanged(int)));
    m_ui->listWidget->setCurrentRow(row);
}

//---------------------------------------------------------
DlgSelectServices::~DlgSelectServices()
{
    delete m_ui;
}

//---------------------------------------------------------
void DlgSelectServices::onCurrentRowChanged(int row)
{
    QListWidgetItem* item = m_ui->listWidget->item(row);
    IStreamingService* plugin = Services::streamingServices()->plugin(item->text());
    if(plugin)
    {
        m_ui->textBrowser->setHtml(
              QObject::tr("<h1>%1</h1>"
                          "<h2>Description</h2>"
                          "%2"
                          "<h2>Service information</h2>"
                          "<p><strong>Maintainer: </strong><a href=%3>%4</a></p>"
                          "<p><strong>Version: </strong>%5</p>")
              .arg(plugin->metaData().name)
              .arg(plugin->metaData().description)
              .arg(plugin->metaData().author_website)
              .arg(plugin->metaData().author)
              .arg(plugin->metaData().version));
        m_ui->labelFlash->setVisible(
            plugin->flashRequired() && !Services::hasFlash());
    }
}

//---------------------------------------------------------
QString DlgSelectServices::selectService(QWidget *parent)
{
    DlgSelectServices dlg(parent);
    if(dlg.exec() == QDialog::Accepted)
    {
        QString serviceName = dlg.m_ui->listWidget->currentItem()->text();
        return serviceName;
    }
    return "";
}
