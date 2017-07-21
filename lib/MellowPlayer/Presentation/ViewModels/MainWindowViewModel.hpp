#pragma once

#include "UpdaterViewModel.hpp"
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <QtQml/QQmlApplicationEngine>

namespace MellowPlayer::Application
{
    class Settings;
    class ILogger;
    class IPlayer;
    class IQtApplication;
}

namespace MellowPlayer::Presentation
{
    class ApplicationViewModel;
    class ListeningHistoryViewModel;
    class StreamingServicesControllerViewModel;
    class ThemeViewModel;

    class MainWindowViewModel : public QObject, public Application::IMainWindow
    {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    public:
        MainWindowViewModel(StreamingServicesControllerViewModel &streamingServicesModel,
                            ListeningHistoryViewModel &listeningHistoryModel, ThemeViewModel &themeViewModel,
                            UpdaterViewModel &updaterViewModel, Application::IQtApplication &qtApp,
                            Application::IPlayer &player, Application::Settings &settings);
        bool load() override;
        void show() override;
        void hide() override;
        bool isVisible() const;

    signals:
        void visibleChanged();

    private slots:
        void setVisible(bool value);

    private:
        bool visible = false;
        Application::ILogger &logger;
        Application::Settings &settings;
        StreamingServicesControllerViewModel &streamingServices;
        ListeningHistoryViewModel &listeningHistory;
        QQmlApplicationEngine qmlApplicationEngine;
        ClipBoardViewModel clipBoardModel;
        SettingsViewModel settingsViewModel;
        UpdaterViewModel &updaterViewModel;
    };
}
