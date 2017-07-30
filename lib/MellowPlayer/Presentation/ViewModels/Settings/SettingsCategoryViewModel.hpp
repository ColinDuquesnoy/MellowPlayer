#pragma once

#include <MellowPlayer/Application/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/SettingListModel.hpp>
#include <QtCore/QAbstractItemModel>

template <class T>
class QQmlObjectListModel;

namespace MellowPlayer::Presentation
{
    class SettingsCategoryViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString icon READ icon CONSTANT)
        Q_PROPERTY(QString qmlComponent READ qmlComponent CONSTANT)
        Q_PROPERTY(QAbstractItemModel* settings READ settingsModel CONSTANT)
    public:
        SettingsCategoryViewModel(ThemeViewModel& themeViewModel, Application::SettingsCategory* settingsCategory = nullptr,
                                  QObject* parent = nullptr);

        virtual QString name() const;
        virtual QString icon() const;
        virtual QString qmlComponent() const;

        SettingListModel* settingsModel();

        Q_INVOKABLE void restoreDefaults();

    private:
        Application::SettingsCategory* settingsCategory_;
        SettingListModel* settingsListModel_;
        SettingViewModelFactory settingViewModelFactory_;
    };

    class CustomSettingsCategoryViewModel : public SettingsCategoryViewModel
    {
        Q_OBJECT
    public:
        CustomSettingsCategoryViewModel(const QString& name, const QString& icon, const QString& qmlComponent, ThemeViewModel& themeViewModel,
                                        QObject* parent = nullptr);

        QString name() const override;
        QString icon() const override;
        QString qmlComponent() const override;

    private:
        QString name_;
        QString icon_;
        QString qmlComponent_;
    };
}
