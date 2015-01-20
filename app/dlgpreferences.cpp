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

#include <QFileDialog>
#include <QMessageBox>
#include <mellowplayer.h>

#include "application.h"
#include "cookiejar.h"
#include "dlgpreferences.h"
#include "icons.h"
#include "keysequenceedit.h"
#include "mainwindow.h"
#include "shortcuts.h"
#include "ui_mainwindow.h"
#include "ui_dlg_preferences.h"

//---------------------------------------------------------
DlgPreferences::DlgPreferences(MainWindow* parent):
    QDialog(parent),
    mainWindow(parent),
    lockPluginState(true)
{
    qDebug() << QSettings().fileName();

    ui = new Ui::DialogPreferences();
    ui->setupUi(this);
    this->setWindowTitle(tr("Preferences"));

    ui->listWidget->item(0)->setIcon(Icons::interface());
    ui->listWidget->item(1)->setIcon(Icons::shortcuts());
    ui->listWidget->item(2)->setIcon(Icons::plugins());
    ui->listWidget->item(3)->setIcon(Icons::userTrash());

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)),
            this, SLOT(onCategoryChanged(int)));
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),
            this, SLOT(reset()));
    connect(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults), SIGNAL(clicked()),
            this, SLOT(restoreDefaults()));

    connect(ui->lineEditTrayIcon, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateTrayIcon(const QString &)));
    connect(ui->toolButtonSelectTrayIcon, SIGNAL(clicked()),
            this, SLOT(chooseTrayIconFile()));

    connect(ui->comboBoxPlugins, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCurrentPluginChanged(int)));
    connect(ui->pushButtonClearCookies, SIGNAL(clicked()),
            this, SLOT(onClearCookiesClicked()));
    connect(ui->pushButtonClearPreferences, SIGNAL(clicked()),
            this, SLOT(onClearPreferencesClicked()));

    connect(ui->checkBoxPluginState, SIGNAL(stateChanged(int)),
            this, SLOT(onPluginStateChanged(int)));

    // empty page
    ui->stackedWidgetPluginSettings->addWidget(new QWidget());

    // load plugins
    ui->comboBoxPlugins->clear();
    foreach(IExtension* plugin, Services::extensions()->plugins())
    {
        QWidget* settings = plugin->settingsWidget();
        int index = 0;
        if(settings)
            index = ui->stackedWidgetPluginSettings->addWidget(settings);
        ui->comboBoxPlugins->addItem(plugin->metaData().name, index);
    }

    reset();

    this->lockPluginState = false;

    // restore last preferences page
    int currentIndex = QSettings().value("lastPreferencesPageIndex", 0).toInt();
    ui->listWidget->setCurrentRow(currentIndex);
}

//---------------------------------------------------------
DlgPreferences::~DlgPreferences()
{
    delete ui;
}

//---------------------------------------------------------
bool DlgPreferences::editPreferences(MainWindow *parent)
{
    DlgPreferences dlg(parent);
    if (dlg.exec())
    {
        dlg.applyInterface();
        dlg.applyShortcuts();
        dlg.applyPlugins();
        return true;
    }
    return false;
}

//---------------------------------------------------------
void DlgPreferences::onCategoryChanged(int category)
{
    ui->stackedWidget->setCurrentIndex(category);
}

//---------------------------------------------------------
void DlgPreferences::reset()
{
    resetInterface();
    resetShortcuts();
    resetPlugins();
}

//---------------------------------------------------------
void DlgPreferences::restoreDefaults()
{
    restoreInterface();
    restoreShortcuts();
    restorePlugins();
}

//---------------------------------------------------------
void DlgPreferences::updateTrayIcon(const QString &iconPath)
{
    ui->labelTrayIcon->setPixmap(trayIconFrom(iconPath).pixmap(24, 24));
}


//---------------------------------------------------------
void DlgPreferences::chooseTrayIconFile()
{
    QString path = QFileDialog::getOpenFileName(
        this, tr("Select a custom tray icon image"), "",
        tr("Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)")
    );
    if(!path.isEmpty())
        this->ui->lineEditTrayIcon->setText(path);
}

//---------------------------------------------------------
void DlgPreferences::onCurrentPluginChanged(int currentIndex)
{
    this->lockPluginState = true;
    QString pluginName = ui->comboBoxPlugins->itemText(currentIndex);
    qDebug() << "Active plugin changed" << pluginName;
    IExtension* plugin = Services::extensions()->plugin(pluginName);
    if(plugin)
    {
        ui->labelPluginAuthor->setText(plugin->metaData().author);
        ui->labelPluginDescription->setText(plugin->metaData().description);
        ui->labelPluginVersion->setText(plugin->metaData().version);
        ui->labelPluginWebSite->setText(plugin->metaData().website);

        int index = ui->comboBoxPlugins->itemData(
            ui->comboBoxPlugins->currentIndex()).toInt();
        ui->stackedWidgetPluginSettings->setCurrentIndex(index);
        ui->checkBoxPluginState->setChecked(
            QSettings().value(plugin->metaData().name, true).toBool());
    }
    else
    {
        ui->labelPluginAuthor->setText("");
        ui->labelPluginDescription->setText("");
        ui->labelPluginVersion->setText("");
        ui->labelPluginWebSite->setText("");
        ui->stackedWidgetPluginSettings->setCurrentIndex(0);
        ui->checkBoxPluginState->setChecked(false);
    }
    this->lockPluginState = false;
}

//---------------------------------------------------------
void DlgPreferences::onPluginStateChanged(int state)
{
    if(this->lockPluginState)
        return;
    IExtension* plugin = Services::extensions()->plugin(
        ui->comboBoxPlugins->currentText());
    if(plugin)
        QSettings().setValue(plugin->metaData().name, bool(state));
    this->restart();
}

//---------------------------------------------------------
void DlgPreferences::restart()
{
    if(QMessageBox::question(
        this, tr("Restart required"),
        tr("You need to restart the application for the change to be applied."
        "\n\n"
        "Do you want to restart now?"), QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes) == QMessageBox::Yes)
    {
        QProcess::startDetached(QApplication::applicationFilePath());
        MellowPlayerApp* app = qobject_cast<MellowPlayerApp*>(qApp);
        app->close();
        qApp->exit(12);
    }
}

void DlgPreferences::onClearCookiesClicked()
{
    if(QMessageBox::question(
        this, tr("Clear cookies"),
        tr("This will remove all cookies stored by Mellow Player.\n"
           "Are you sure you want to clear all cookies?"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No) ==
            QMessageBox::Yes)
    {
        CookieJar().purgeCookies();
        restart();
    }
}

//---------------------------------------------------------
void DlgPreferences::onClearPreferencesClicked()
{
    if(QMessageBox::question(
        this, tr("Clear settings"),
        tr("This will remove all settings stored by Mellow Player.\n"
           "Are you sure you want to erase all settings?"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No) ==
            QMessageBox::Yes)
    {
        QSettings().clear();
        restart();
    }
}


//---------------------------------------------------------
void DlgPreferences::resetInterface()
{
    bool minimizeToTray = QSettings().value(
        "minimizeToTray", QVariant(true)).toBool();
    QString trayIconPath = QSettings().value(
                "trayIcon",  ":/icons/mellowplayer.png").toString();
    bool confirmQuit = QSettings().value("confirmQuit", true).toBool();

    ui->checkBoxConfirmQuit->setChecked(confirmQuit);
    ui->checkBoxMinimizeToTray->setChecked(minimizeToTray);
    ui->lineEditTrayIcon->setText(trayIconPath);
    updateTrayIcon(trayIconPath);
}


//---------------------------------------------------------
void DlgPreferences::resetShortcuts()
{
    QList<QAction*> actions;
    actions.append(mainWindow->ui->actionPlayPause);
    actions.append(mainWindow->ui->actionStop);
    actions.append(mainWindow->ui->actionNext);
    actions.append(mainWindow->ui->actionPrevious);

    QList<QString> shortcuts;
    shortcuts.append(DEFAULT_SHORTCUT_PLAY);
    shortcuts.append(DEFAULT_SHORTCUT_STOP);
    shortcuts.append(DEFAULT_SHORTCUT_NEXT);
    shortcuts.append(DEFAULT_SHORTCUT_PREVIOUS);

    QList<KeySequenceEdit*> edits;
    edits.append(ui->lineEditPlayPause);
    edits.append(ui->lineEditStop);
    edits.append(ui->lineEditNext);
    edits.append(ui->lineEditPrevious);

    for(int i=0; i < actions.count(); ++ i)
        edits[i]->setKeySequence(
            QSettings().value(actions[i]->objectName(),
                              shortcuts[i]).toString());
}

//---------------------------------------------------------
void DlgPreferences::resetPlugins()
{
    this->lockPluginState = true;
    for(int i = 0; i < ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = ui->stackedWidgetPluginSettings->widget(widgetIndex);
            IExtension* plugin = Services::extensions()->plugin(
                ui->comboBoxPlugins->itemText(i));
            plugin->resetSettings(w);
        }
    }
    this->lockPluginState = false;
}

//---------------------------------------------------------
void DlgPreferences::restoreInterface()
{
    this->lockPluginState = true;
    QSettings().setValue("minimizeToTray", true);
    QSettings().setValue("trayIcon",  ":/icons/mellowplayer.png");
    QSettings().setValue("confirmQuit", true);

    this->resetInterface();
    this->lockPluginState = false;
}

//---------------------------------------------------------
void DlgPreferences::restoreShortcuts()
{
    QList<QAction*> actions;
    actions.append(mainWindow->ui->actionPlayPause);
    actions.append(mainWindow->ui->actionStop);
    actions.append(mainWindow->ui->actionNext);
    actions.append(mainWindow->ui->actionPrevious);

    QList<QString> shortcuts;
    shortcuts.append(DEFAULT_SHORTCUT_PLAY);
    shortcuts.append(DEFAULT_SHORTCUT_STOP);
    shortcuts.append(DEFAULT_SHORTCUT_NEXT);
    shortcuts.append(DEFAULT_SHORTCUT_PREVIOUS);

    for(int i=0; i < actions.count(); ++ i)
        QSettings().setValue(actions[i]->objectName(), shortcuts[i]);

    this->resetShortcuts();
}

//---------------------------------------------------------
void DlgPreferences::restorePlugins()
{
    for(int i = 0; i < ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = ui->stackedWidgetPluginSettings->widget(widgetIndex);
            IExtension* plugin = Services::extensions()->plugin(
                        ui->comboBoxPlugins->itemText(i));
            plugin->restoreDefaultSettings(w);
        }
    }

    this->resetPlugins();
}

//---------------------------------------------------------
void DlgPreferences::applyInterface()
{
    QSettings().setValue("minimizeToTray",
                         ui->checkBoxMinimizeToTray->isChecked());
    QSettings().setValue("trayIcon", ui->lineEditTrayIcon->text());
    QSettings().setValue("confirmQuit", ui->checkBoxConfirmQuit->isChecked());
    mainWindow->trayIcon->setIcon(trayIconFrom(ui->lineEditTrayIcon->text()));
}

//---------------------------------------------------------
void DlgPreferences::applyShortcuts()
{
    QList<QAction*> actions;
    actions.append(mainWindow->ui->actionPlayPause);
    actions.append(mainWindow->ui->actionStop);
    actions.append(mainWindow->ui->actionNext);
    actions.append(mainWindow->ui->actionPrevious);

    QList<KeySequenceEdit*> edits;
    edits.append(ui->lineEditPlayPause);
    edits.append(ui->lineEditStop);
    edits.append(ui->lineEditNext);
    edits.append(ui->lineEditPrevious);

    for(int i = 0; i < actions.count(); ++i)
    {
        QSettings().setValue(actions[i]->objectName(),
                             edits[i]->keySequence().toString());
        actions[i]->setShortcut(edits[i]->keySequence());
    }
}

//---------------------------------------------------------
void DlgPreferences::applyPlugins()
{
    for(int i = 0; i < ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = ui->stackedWidgetPluginSettings->widget(widgetIndex);
            IExtension* plugin = Services::extensions()->plugin(
                        ui->comboBoxPlugins->itemText(i));
            plugin->applySettings(w);
        }
    }
}

//---------------------------------------------------------
QIcon DlgPreferences::trayIconFrom(const QString& path)
{
    if(QFile(path).exists())
        return QIcon(path);
    return QIcon::fromTheme(path);
}

