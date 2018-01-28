#pragma once

#include "SettingsCategoryViewModel.hpp"
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/SettingsCategoryListModel.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QObject>

namespace MellowPlayer::Domain
{
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class SettingViewModel;
    class ThemeViewModel;

    class SettingsViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* categories READ categories CONSTANT)
    public:
        SettingsViewModel(Domain::Settings& settings,
                          ThemeViewModel& themeViewModel,
                          IContextProperties& contextProperties);

        SettingsCategoryListModel* categories() const;

        Q_INVOKABLE SettingViewModel* get(int key);
        Q_INVOKABLE void restoreDefaults();

        void initialize(IQmlApplicationEngine& qmlApplicationEngine) override;

    private:
        Domain::Settings& settings_;
        SettingViewModelFactory factory_;
        SettingsCategoryListModel* categories_;
    };
}
