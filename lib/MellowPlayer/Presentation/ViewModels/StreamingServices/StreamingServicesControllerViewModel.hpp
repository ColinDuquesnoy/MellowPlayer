#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>
#include <MellowPlayer/Application/ICommandLineParser.hpp>

class QQmlApplicationEngine;
namespace MellowPlayer::Application {

    class Settings;
    class Setting;
    class Players;
    class StreamingServicesController;
    class StreamingService;
    class IWorkDispatcher;
    class IStreamingServiceCreator;
    class ICommandLineParser;

}

namespace MellowPlayer::Presentation {

    class StreamingServicesControllerViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QAbstractListModel* allServices READ getAllServices CONSTANT)
        Q_PROPERTY(QAbstractItemModel* enabledServices READ getEnabledServices CONSTANT)
        Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
        Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
        Q_PROPERTY(bool isCurrentServiceRunning READ isCurrentServiceRunning NOTIFY isCurrentServiceRunningChanged)
    public:
        StreamingServicesControllerViewModel(Application::StreamingServicesController& streamingServices,
                                             Application::Players& players,
                                             Application::Settings& settings,
                                             Application::IWorkDispatcher& workDispatcher,
                                             Application::IStreamingServiceCreator& streamingServiceCreator,
                                             Application::ICommandLineParser& commandLineParser);
        void initialize();

        Q_INVOKABLE void reload();
        StreamingServiceListModel* getAllServices() { return allServices; }
        StreamingServiceProxyListModel* getEnabledServices() { return &enabledServices; }
        StreamingServiceViewModel* getCurrentService() const;
        int getCurrentIndex() const;
        bool isCurrentServiceRunning() const;

        Q_INVOKABLE int getWebViewIndex(const QString& serviceName) const;

        Q_INVOKABLE void next();
        Q_INVOKABLE void previous();
        Q_INVOKABLE void createService(const QString& serviceName, const QString& serviceUrl, const QString& authorName, const QString& authorWebsite);

    public slots:
        void setCurrentService(QObject* value);
        void setCurrentIndex(int value);

    signals:
        void currentServiceChanged(QObject* currentService);
        void currentIndexChanged(int currentIndex);
        void isCurrentServiceRunningChanged();
        void serviceCreated(const QString& directory);

    private slots:
        void onServiceAdded(Application::StreamingService* streamingService);
        void onPlayerRunningChanged();
        void onServiceEnabledChanged();

    private:
        int getNextIndex(int index) const;
        int getPreviousIndex(int index) const;

        Application::StreamingServicesController& streamingServices;
        Application::Players& players;
        Application::Settings& settings;
        Application::Setting& currentServiceSetting;
        Application::IWorkDispatcher& workDispatcher;
        Application::IStreamingServiceCreator& streamingServiceCreator;
        Application::ICommandLineParser& commandLineParser;
        StreamingServiceListModel* allServices;
        StreamingServiceProxyListModel enabledServices;
        StreamingServiceViewModel* currentService = nullptr;
        int currentIndex = -1;
        bool isCurrentServiceRunning_ = false;
    };

}
