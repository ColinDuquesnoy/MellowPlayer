#include <mellowplayer.h>

#include "dlgpreferences.h"
#include "mainwindow.h"
#include "shortcuts.h"
#include "ui_mainwindow.h"
#include "ui_dlg_preferences.h"

//---------------------------------------------------------
DlgPreferences::DlgPreferences(MainWindow* parent):
    QDialog(parent),
    mainWindow(parent)
{
    qDebug() << QSettings().fileName();

    ui = new Ui::DialogPreferences();
    ui->setupUi(this);

    this->setWindowTitle(tr("Preferences"));

    connect(ui->listWidget, &QListWidget::currentRowChanged,
            this, &DlgPreferences::onCategoryChanged);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset),
            &QPushButton::clicked, this, &DlgPreferences::reset);
    connect(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults),
            &QPushButton::clicked, this, &DlgPreferences::restoreDefaults);

    connect(ui->lineEditTrayIcon, &QLineEdit::textChanged,
            this, &DlgPreferences::updateTrayIcon);
    connect(ui->toolButtonSelectTrayIcon, &QToolButton::clicked,
            this, &DlgPreferences::chooseTrayIconFile);

    connect(ui->comboBoxPlugins, &QComboBox::currentTextChanged,
            this, &DlgPreferences::onCurrentPluginChanged);

    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        ui->listWidget->setCurrentRow(i);
        reset();
    }

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
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        resetInterface();
        break;
    case 1:
        resetShortcuts();
        break;
    case 2:
        resetPlugins();
        break;
    }
}

//---------------------------------------------------------
void DlgPreferences::restoreDefaults()
{
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        restoreInterface();
        break;
    case 1:
        restoreShortcuts();
        break;
    case 2:
        restorePlugins();
        break;
    }
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
void DlgPreferences::onCurrentPluginChanged(const QString& pluginName)
{
    qDebug() << "Active plugin changed" << pluginName;
    ExtensionPlugin* plugin = NULL;
    if(!pluginName.isEmpty())
        plugin = Services::extensions()->plugin(pluginName);
    if(plugin)
    {
        ui->labelPluginAuthor->setText(plugin->metaData.author);
        ui->labelPluginDescription->setText(plugin->interface->description());
        ui->labelPluginVersion->setText(plugin->metaData.version);
        ui->labelPluginWebSite->setText(plugin->metaData.website);
    }
    else
    {
        ui->labelPluginAuthor->setText("");
        ui->labelPluginDescription->setText("");
        ui->labelPluginVersion->setText("");
        ui->labelPluginWebSite->setText("");
    }
}


//---------------------------------------------------------
void DlgPreferences::resetInterface()
{
    bool minimizeToTray = QSettings().value(
        "minimizeToTray", QVariant(true)).toBool();
    QString trayIconPath = QSettings().value(
                "trayIcon",  ":/icons/mellowplayer.png").toString();

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

    QList<QKeySequenceEdit*> edits;
    edits.append(ui->keySequenceEditPlayPause);
    edits.append(ui->keySequenceEditStop);
    edits.append(ui->keySequenceEditNext);
    edits.append(ui->keySequenceEditPrevious);

    for(int i=0; i < actions.count(); ++ i)
        edits[i]->setKeySequence(
            QSettings().value(actions[i]->objectName(),
                              shortcuts[i]).toString());
}

//---------------------------------------------------------
void DlgPreferences::resetPlugins()
{
    ui->comboBoxPlugins->clear();
    foreach(ExtensionPlugin* plugin, Services::extensions()->plugins())
        ui->comboBoxPlugins->addItem(plugin->metaData.name);
}

//---------------------------------------------------------
void DlgPreferences::restoreInterface()
{
    QSettings().setValue("minimizeToTray", true);
    QSettings().setValue("trayIcon",  ":/icons/mellowplayer.png");

    this->resetInterface();
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
    // todo add a restore default method to extension plugins.

    this->resetPlugins();
}

void DlgPreferences::applyInterface()
{
    QSettings().setValue("minimizeToTray",
                         ui->checkBoxMinimizeToTray->isChecked());
    QSettings().setValue("trayIcon", ui->lineEditTrayIcon->text());
    mainWindow->trayIcon->setIcon(trayIconFrom(ui->lineEditTrayIcon->text()));
}

void DlgPreferences::applyShortcuts()
{
    QList<QAction*> actions;
    actions.append(mainWindow->ui->actionPlayPause);
    actions.append(mainWindow->ui->actionStop);
    actions.append(mainWindow->ui->actionNext);
    actions.append(mainWindow->ui->actionPrevious);

    QList<QKeySequenceEdit*> edits;
    edits.append(ui->keySequenceEditPlayPause);
    edits.append(ui->keySequenceEditStop);
    edits.append(ui->keySequenceEditNext);
    edits.append(ui->keySequenceEditPrevious);

    for(int i = 0; i < actions.count(); ++i)
    {
        QSettings().setValue(actions[i]->objectName(),
                             edits[i]->keySequence().toString());
        actions[i]->setShortcut(edits[i]->keySequence());
    }
}

void DlgPreferences::applyPlugins()
{
    // todo add a restore default method to extension plugins.
}

//---------------------------------------------------------
QIcon DlgPreferences::trayIconFrom(const QString& path)
{
    if(QFile(path).exists())
        return QIcon(path);
    return QIcon::fromTheme(path);
}

