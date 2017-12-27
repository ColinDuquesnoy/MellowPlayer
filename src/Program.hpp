#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Network/ApplicationNetworkProxy.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <MellowPlayer/Presentation/Mpris/IMprisService.hpp>
#include <MellowPlayer/Presentation/ViewModels/ViewModels.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifications.hpp>
#include <MellowPlayer/Presentation/Hotkeys/IHotkeys.hpp>

namespace MellowPlayer::Main
{
    class Program: public QObject
    {
        Q_OBJECT
    public:
        static int main(int argc, char** argv);

        Program(Infrastructure::IApplication& application,
                Infrastructure::ApplicationNetworkProxy& applicationNetworkProxy,
                Presentation::IContextProperties& contextProperties,
                Presentation::IMprisService& mprisService,
                Presentation::IViewModels& viewModels,
                Presentation::ISystemTrayIcon& systemTrayIcon,
                Presentation::INotifications& notifications,
                Presentation::IHotkeys& hotkeys);
        int run();

    private slots:
        void initialize();
        void finished();

    private:
        Infrastructure::IApplication& application_;
        Infrastructure::ApplicationNetworkProxy& applicationNetworkProxy_;
        Presentation::IContextProperties& contextProperties_;
        Presentation::IMprisService& mprisService_;
        Presentation::IViewModels& viewModels_;
        Presentation::ISystemTrayIcon& systemTrayIcon_;
        Presentation::INotifications& notifications_;
        Presentation::IHotkeys& hotkeys_;
    };
}
