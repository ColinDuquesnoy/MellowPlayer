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
    m_mainWindow(parent),
    m_lockPluginState(true)
{
    qDebug() << QSettings().fileName();

    m_ui = new Ui::DialogPreferences();
    m_ui->setupUi(this);
    setWindowTitle(tr("Preferences"));

    m_ui->listWidget->item(0)->setIcon(Icons::interface());
    m_ui->listWidget->item(1)->setIcon(Icons::shortcuts());
    m_ui->listWidget->item(2)->setIcon(Icons::plugins());
    m_ui->listWidget->item(3)->setIcon(Icons::userTrash());

    connect(m_ui->listWidget, SIGNAL(currentRowChanged(int)),
            this, SLOT(onCategoryChanged(int)));
    connect(m_ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),
            this, SLOT(reset()));
    connect(m_ui->buttonBox->button(QDialogButtonBox::RestoreDefaults), SIGNAL(clicked()),
            this, SLOT(restoreDefaults()));

    connect(m_ui->comboBoxPlugins, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCurrentPluginChanged(int)));
    connect(m_ui->pushButtonClearCookies, SIGNAL(clicked()),
            this, SLOT(onClearCookiesClicked()));
    connect(m_ui->pushButtonClearPreferences, SIGNAL(clicked()),
            this, SLOT(onClearPreferencesClicked()));

    connect(m_ui->checkBoxPluginState, SIGNAL(stateChanged(int)),
            this, SLOT(onPluginStateChanged(int)));

    // empty page
    m_ui->stackedWidgetPluginSettings->addWidget(new QWidget());

    // load plugins
    m_ui->comboBoxPlugins->clear();
    foreach(IExtension* plugin, Services::extensions()->plugins())
    {
        QWidget* settings = plugin->settingsWidget();
        int index = 0;
        if(settings)
            index = m_ui->stackedWidgetPluginSettings->addWidget(settings);
        m_ui->comboBoxPlugins->addItem(plugin->metaData().name, index);
    }

    reset();

    m_lockPluginState = false;

    // restore last preferences page
    int currentIndex = QSettings().value("lastPreferencesPageIndex", 0).toInt();
    m_ui->listWidget->setCurrentRow(currentIndex);
}

//---------------------------------------------------------
DlgPreferences::~DlgPreferences()
{
    delete m_ui;
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
    m_ui->stackedWidget->setCurrentIndex(category);
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
void DlgPreferences::onCurrentPluginChanged(int currentIndex)
{
    m_lockPluginState = true;
    QString pluginName = m_ui->comboBoxPlugins->itemText(currentIndex);
    qDebug() << "Active plugin changed" << pluginName;
    IExtension* plugin = Services::extensions()->plugin(pluginName);
    if(plugin)
    {
        m_ui->labelPluginAuthor->setText(plugin->metaData().author);
        m_ui->labelPluginDescription->setText(plugin->metaData().description);
        m_ui->labelPluginVersion->setText(plugin->metaData().version);
        m_ui->labelPluginWebSite->setText(plugin->metaData().author_website);

        int index = m_ui->comboBoxPlugins->itemData(
            m_ui->comboBoxPlugins->currentIndex()).toInt();
        m_ui->stackedWidgetPluginSettings->setCurrentIndex(index);
        m_ui->checkBoxPluginState->setChecked(
            QSettings().value(plugin->metaData().name, true).toBool());
    }
    else
    {
        m_ui->labelPluginAuthor->setText("");
        m_ui->labelPluginDescription->setText("");
        m_ui->labelPluginVersion->setText("");
        m_ui->labelPluginWebSite->setText("");
        m_ui->stackedWidgetPluginSettings->setCurrentIndex(0);
        m_ui->checkBoxPluginState->setChecked(false);
    }
    m_lockPluginState = false;
}

//---------------------------------------------------------
void DlgPreferences::onPluginStateChanged(int state)
{
    if(m_lockPluginState)
        return;
    IExtension* plugin = Services::extensions()->plugin(
        m_ui->comboBoxPlugins->currentText());
    if(plugin)
        QSettings().setValue(plugin->metaData().name, bool(state));
    restart();
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

//---------------------------------------------------------
void DlgPreferences::onClearCookiesClicked()
{
    if(QMessageBox::question(
        this, tr("Clear cookies"),
        tr("This will remove all cookies stored by MellowPlayer.\n"
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
        tr("This will remove all settings stored by MellowPlayer.\n"
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

    m_ui->checkBoxConfirmQuit->setChecked(confirmQuit);
    m_ui->checkBoxMinimizeToTray->setChecked(minimizeToTray);
}


//---------------------------------------------------------
void DlgPreferences::resetShortcuts()
{
    QList<QAction*> actions;
    actions.append(m_mainWindow->m_ui->actionPlayPause);
    actions.append(m_mainWindow->m_ui->actionStop);
    actions.append(m_mainWindow->m_ui->actionNext);
    actions.append(m_mainWindow->m_ui->actionPrevious);
    actions.append(m_mainWindow->m_ui->actionAdd_to_favorites);

    QList<QString> shortcuts;
    shortcuts.append(DEFAULT_SHORTCUT_PLAY);
    shortcuts.append(DEFAULT_SHORTCUT_STOP);
    shortcuts.append(DEFAULT_SHORTCUT_NEXT);
    shortcuts.append(DEFAULT_SHORTCUT_PREVIOUS);
    shortcuts.append(DEFAULT_SHORTCUT_FAVORITE);

    QList<KeySequenceEdit*> edits;
    edits.append(m_ui->lineEditPlayPause);
    edits.append(m_ui->lineEditStop);
    edits.append(m_ui->lineEditNext);
    edits.append(m_ui->lineEditPrevious);
    edits.append(m_ui->lineEditFavorite);

    for(int i=0; i < actions.count(); ++ i)
        edits[i]->setKeySequence(
            QSettings().value(actions[i]->objectName(),
                              shortcuts[i]).toString());
}

//---------------------------------------------------------
void DlgPreferences::resetPlugins()
{
    m_lockPluginState = true;
    for(int i = 0; i < m_ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = m_ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = m_ui->stackedWidgetPluginSettings->widget(widgetIndex);
            IExtension* plugin = Services::extensions()->plugin(
                m_ui->comboBoxPlugins->itemText(i));
            plugin->resetSettings(w);
        }
    }
    m_lockPluginState = false;
}

//---------------------------------------------------------
void DlgPreferences::restoreInterface()
{
    m_lockPluginState = true;
    QSettings().setValue("minimizeToTray", true);
    QSettings().setValue("trayIcon",  ":/icons/mellowplayer.png");
    QSettings().setValue("confirmQuit", true);

    resetInterface();
    m_lockPluginState = false;
}

//---------------------------------------------------------
void DlgPreferences::restoreShortcuts()
{
    QList<QAction*> actions;
    actions.append(m_mainWindow->m_ui->actionPlayPause);
    actions.append(m_mainWindow->m_ui->actionStop);
    actions.append(m_mainWindow->m_ui->actionNext);
    actions.append(m_mainWindow->m_ui->actionPrevious);
    actions.append(m_mainWindow->m_ui->actionAdd_to_favorites);

    QList<QString> shortcuts;
    shortcuts.append(DEFAULT_SHORTCUT_PLAY);
    shortcuts.append(DEFAULT_SHORTCUT_STOP);
    shortcuts.append(DEFAULT_SHORTCUT_NEXT);
    shortcuts.append(DEFAULT_SHORTCUT_PREVIOUS);
    shortcuts.append(DEFAULT_SHORTCUT_FAVORITE);

    for(int i=0; i < actions.count(); ++ i)
        QSettings().setValue(actions[i]->objectName(), shortcuts[i]);

    resetShortcuts();
}

//---------------------------------------------------------
void DlgPreferences::restorePlugins()
{
    for(int i = 0; i < m_ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = m_ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            IExtension* plugin = Services::extensions()->plugin(
                        m_ui->comboBoxPlugins->itemText(i));
            plugin->restoreDefaultSettings();
        }
    }

    resetPlugins();
}

//---------------------------------------------------------
void DlgPreferences::applyInterface()
{
    QSettings().setValue("minimizeToTray",
                         m_ui->checkBoxMinimizeToTray->isChecked());
    QSettings().setValue("confirmQuit", m_ui->checkBoxConfirmQuit->isChecked());
}

//---------------------------------------------------------
void DlgPreferences::applyShortcuts()
{
    QList<QAction*> actions;
    actions.append(m_mainWindow->m_ui->actionPlayPause);
    actions.append(m_mainWindow->m_ui->actionStop);
    actions.append(m_mainWindow->m_ui->actionNext);
    actions.append(m_mainWindow->m_ui->actionPrevious);
    actions.append(m_mainWindow->m_ui->actionAdd_to_favorites);

    QList<KeySequenceEdit*> edits;
    edits.append(m_ui->lineEditPlayPause);
    edits.append(m_ui->lineEditStop);
    edits.append(m_ui->lineEditNext);
    edits.append(m_ui->lineEditPrevious);
    edits.append(m_ui->lineEditFavorite);

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
    for(int i = 0; i < m_ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = m_ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = m_ui->stackedWidgetPluginSettings->widget(widgetIndex);
            IExtension* plugin = Services::extensions()->plugin(
                        m_ui->comboBoxPlugins->itemText(i));
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

