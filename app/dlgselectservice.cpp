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

#include <mellowplayer.h>
#include "dlgselectservice.h"
#include "ui_dlg_select_service.h"


//---------------------------------------------------------
DlgSelectServices::DlgSelectServices(QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogSelectServices())
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem *)),
            this, SLOT(onCurrentItemChanged(QListWidgetItem *)));

    int row = 0;
    foreach(IStreamingServiceIntegration* plugin,
            Services::streamingServices()->plugins()){
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setText(plugin->metaData().name);
        item->setIcon(plugin->metaData().icon);
        ui->listWidget->addItem(item);
    }
    ui->listWidget->setCurrentRow(row);
}

//---------------------------------------------------------
DlgSelectServices::~DlgSelectServices()
{
    delete ui;
}

//---------------------------------------------------------
void DlgSelectServices::onCurrentItemChanged(QListWidgetItem *item)
{
    if(!item)
        return;
    IStreamingServiceIntegration* plugin = Services::streamingServices()->plugin(item->text());
    if(plugin)
    {
        ui->textBrowser->setHtml(
              QObject::tr("<h1>%1</h1>"
                          "<h2>Description</h2>"
                          "%2"
                          "<h2>Service information</h2>"
                          "<p><strong>Maintainer: </strong><a href=%3>%4</a></p>"
                          "<p><strong>Version: </strong>%5</p>")
              .arg(plugin->metaData().name)
              .arg(plugin->metaData().description)
              .arg(plugin->metaData().website)
              .arg(plugin->metaData().author)
              .arg(plugin->metaData().version));
    }
}

//---------------------------------------------------------
QString DlgSelectServices::selectService(QWidget *parent)
{
    DlgSelectServices dlg(parent);
    if(dlg.exec() == QDialog::Accepted)
        return dlg.ui->listWidget->currentItem()->text();
    return "";
}
