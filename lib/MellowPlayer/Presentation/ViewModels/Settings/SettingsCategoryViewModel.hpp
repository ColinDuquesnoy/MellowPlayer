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
        Q_PROPERTY(QString name READ getName CONSTANT)
        Q_PROPERTY(QString icon READ getIcon CONSTANT)
        Q_PROPERTY(QString qmlComponent READ getQmlComponent CONSTANT)
        Q_PROPERTY(QAbstractItemModel *settings READ getSettingsModel CONSTANT)
    public:
        SettingsCategoryViewModel(ThemeViewModel &themeViewModel, Application::SettingsCategory *settingsCategory = nullptr,
                                  QObject *parent = nullptr);

        virtual QString getName() const;
        virtual QString getIcon() const;
        virtual QString getQmlComponent() const;
        ;
        SettingListModel *getSettingsModel();

        Q_INVOKABLE void restoreDefaults();

    private:
        Application::SettingsCategory *settingsCategory;
        SettingListModel *settingsListModel;
        SettingViewModelFactory settingViewModelFactory;
    };

    class CustomSettingsCategoryViewModel : public SettingsCategoryViewModel
    {
        Q_OBJECT
    public:
        CustomSettingsCategoryViewModel(const QString &name, const QString &icon, const QString &qmlComponent, ThemeViewModel &themeViewModel,
                                        QObject *parent = nullptr);

        QString getName() const override;
        QString getIcon() const override;
        QString getQmlComponent() const override;

    private:
        QString name;
        QString icon;
        QString qmlComponent;
    };
}
