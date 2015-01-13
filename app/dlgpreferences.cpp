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
    connect(ui->checkBoxPluginState, &QCheckBox::stateChanged,
            this, &DlgPreferences::onPluginStateChanged);

    // empty page
    ui->stackedWidgetPluginSettings->addWidget(new QWidget());

    // load plugins
    ui->comboBoxPlugins->clear();
    foreach(ExtensionPlugin* plugin, Services::extensions()->plugins())
    {
        QWidget* settings = plugin->iExtension->settingsWidget();
        int index = 0;
        if(settings)
            index = ui->stackedWidgetPluginSettings->addWidget(settings);
        ui->comboBoxPlugins->addItem(plugin->metaData.name, index);
    }

    reset();

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
void DlgPreferences::onCurrentPluginChanged(const QString& pluginName)
{
    qDebug() << "Active plugin changed" << pluginName;
    ExtensionPlugin* plugin = NULL;
    plugin = Services::extensions()->plugin(pluginName);
    if(plugin)
    {
        ui->labelPluginAuthor->setText(plugin->metaData.author);
        ui->labelPluginDescription->setText(plugin->iExtension->description());
        ui->labelPluginVersion->setText(plugin->metaData.version);
        ui->labelPluginWebSite->setText(plugin->metaData.website);

        int index = ui->comboBoxPlugins->itemData(
            ui->comboBoxPlugins->currentIndex()).toInt();
        ui->stackedWidgetPluginSettings->setCurrentIndex(index);
        ui->checkBoxPluginState->setChecked(
            QSettings().value(plugin->metaData.name, true).toBool());
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
}

//---------------------------------------------------------
void DlgPreferences::onPluginStateChanged(int state)
{
    ExtensionPlugin* plugin = Services::extensions()->plugin(
        ui->comboBoxPlugins->currentText());
    if(plugin)
        QSettings().setValue(plugin->metaData.name, bool(state));
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
    for(int i = 0; i < ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = ui->stackedWidgetPluginSettings->widget(widgetIndex);
            ExtensionPlugin* plugin = Services::extensions()->plugin(
                ui->comboBoxPlugins->itemText(i));
            plugin->iExtension->resetSettings(w);
        }
    }
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
    for(int i = 0; i < ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = ui->stackedWidgetPluginSettings->widget(widgetIndex);
            ExtensionPlugin* plugin = Services::extensions()->plugin(
                        ui->comboBoxPlugins->itemText(i));
            plugin->iExtension->restoreDefaultSettings(w);
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

//---------------------------------------------------------
void DlgPreferences::applyPlugins()
{
    for(int i = 0; i < ui->comboBoxPlugins->count(); ++i)
    {
        int widgetIndex = ui->comboBoxPlugins->itemData(i).toInt();
        if(widgetIndex)
        {
            QWidget* w = ui->stackedWidgetPluginSettings->widget(widgetIndex);
            ExtensionPlugin* plugin = Services::extensions()->plugin(
                        ui->comboBoxPlugins->itemText(i));
            plugin->iExtension->applySettings(w);
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

