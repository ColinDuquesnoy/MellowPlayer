#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>

namespace MellowPlayer::Application {

    class Settings;
    class ILogger;
    class IPlayer;
    class IQtApplication;

}

namespace MellowPlayer::Presentation {

    class ApplicationViewModel;
    class ListeningHistoryViewModel;
    class StreamingServicesControllerViewModel;
    class StyleViewModel;

    class MainWindowViewModel: public QObject, public Application::IMainWindow {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    public:
        MainWindowViewModel(StreamingServicesControllerViewModel& streamingServicesModel,
                            ListeningHistoryViewModel& listeningHistoryModel,
                            StyleViewModel& serviceStyleModel,
                            Application::IQtApplication& qtApp,
                            Application::IPlayer& player,
                            Application::Settings& settings);
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
        Application::ILogger& logger;
        Application::Settings& settings;
        StreamingServicesControllerViewModel& streamingServices;
        ListeningHistoryViewModel& listeningHistory;
        QQmlApplicationEngine qmlApplicationEngine;
        ClipBoardViewModel clipBoardModel;
        SettingsViewModel settingsModel;
    };

}
