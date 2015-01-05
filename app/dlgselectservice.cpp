#include <mellowplayer.h>
#include "dlgselectservice.h"
#include "ui_dlg_select_service.h"


DlgSelectServices::DlgSelectServices(QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogSelectServices())
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::currentItemChanged,
            this, &DlgSelectServices::onCurrentItemChanged);

    int row = 0;
    foreach(CloudServicesManager::PluginMetaData meta,
            Services::cloudServices()->allMetaData()){
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setText(meta.name);
        item->setIcon(meta.icon);
        ui->listWidget->addItem(item);
    }
    ui->listWidget->setCurrentRow(row);
}

DlgSelectServices::~DlgSelectServices()
{
    delete ui;
}

void DlgSelectServices::onCurrentItemChanged(QListWidgetItem *item)
{
    if(!item)
        return;
    static QString html =
        "<h1>%1</h1>"
        "<h2>Description</h2>"
        "%2"
        "<h2>Service information</h2>"
        "<p><strong>Maintainer: </strong><a href=%3>%4</a></p>"
        "<p><strong>Version: </strong>%5</p>";
    CloudServicesManager::PluginMetaData meta =
            Services::cloudServices()->metaData(item->text());
    ui->textBrowser->setHtml(html.arg(meta.name, meta.htmlDescription,
                                      meta.website, meta.author, meta.version));
}

QString DlgSelectServices::selectService(QWidget *parent)
{
    DlgSelectServices dlg(parent);
    if(dlg.exec() == QDialog::Accepted)
        return dlg.ui->listWidget->currentItem()->text();
    return "";
}
