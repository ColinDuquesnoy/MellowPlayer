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
    foreach(CloudServicesManager::Plugin plugin,
            Services::cloudServices()->plugins()){
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setText(plugin.name);
        item->setIcon(plugin.icon);
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
    CloudServicesManager::Plugin plugin =
            Services::cloudServices()->plugin(item->text());
    Q_ASSERT(plugin.isValid());
    ui->textBrowser->setHtml(html.arg(
        plugin.name, plugin.htmlDescription, plugin.website, plugin.author,
        plugin.version));
}

QString DlgSelectServices::selectService(QWidget *parent)
{
    DlgSelectServices dlg(parent);
    if(dlg.exec() == QDialog::Accepted)
        return dlg.ui->listWidget->currentItem()->text();
    return "";
}
