#pragma once

#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <QtQml/QQmlApplicationEngine>
#include "DevToolsWindowViewModel.hpp"

namespace MellowPlayer::Domain
{
    class Settings;
    class ILogger;
    class IPlayer;
    class IDeprecatedQtApplication;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel;
    class StreamingServicesControllerViewModel;
    class ThemeViewModel;
    class UpdaterViewModel;

    class MainWindowViewModel : public QObject, public Domain::IMainWindow
    {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    public:
        MainWindowViewModel(StreamingServicesControllerViewModel& streamingServicesModel, ListeningHistoryViewModel& listeningHistoryModel,
                            ThemeViewModel& themeViewModel, UpdaterViewModel& updaterViewModel, Domain::IDeprecatedQtApplication& qtApp,
                            Domain::IPlayer& player, Domain::Settings& settings);
        bool load() override;
        void show() override;
        void hide() override;
        bool isVisible() const;

    signals:
        void visibleChanged();

    private slots:
        void setVisible(bool value);

    private:
        bool visible_ = false;
        Domain::ILogger& logger_;
        Domain::Settings& settings_;
        StreamingServicesControllerViewModel& streamingServices_;
        ListeningHistoryViewModel& listeningHistory_;
        QQmlApplicationEngine qmlApplicationEngine_;
        ClipBoardViewModel clipBoardModel_;
        SettingsViewModel settingsViewModel_;
        UpdaterViewModel& updaterViewModel_;
        DevToolsWindowViewModel devToolsWindowViewModel;
    };
}
