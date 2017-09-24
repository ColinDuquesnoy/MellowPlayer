#pragma once

#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>
#include <QObject>

class QQmlApplicationEngine;

namespace MellowPlayer::Application
{
    class Settings;
    class Setting;
    class Players;
    class StreamingServicesController;
    class StreamingService;
    class IWorkDispatcher;
    class IStreamingServiceCreator;
    class ICommandLineParser;
    class IUserScriptFactory;
}

namespace MellowPlayer::Presentation
{
    class StreamingServicesControllerViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractListModel* allServices READ allServices CONSTANT)
        Q_PROPERTY(QAbstractItemModel* enabledServices READ enabledServices CONSTANT)
        Q_PROPERTY(QObject* currentService READ currentService WRITE setCurrentService NOTIFY currentServiceChanged)
        Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
        Q_PROPERTY(bool isCurrentServiceRunning READ isCurrentServiceRunning NOTIFY isCurrentServiceRunningChanged)
    public:
        StreamingServicesControllerViewModel(Application::StreamingServicesController& streamingServices,
                                             Application::Players& players,
                                             Application::Settings& settings,
                                             Application::IWorkDispatcher& workDispatcher,
                                             Application::IStreamingServiceCreator& streamingServiceCreator,
                                             Application::ICommandLineParser& commandLineParser,
                                             Application::IUserScriptFactory& userScriptFactory);
        void initialize();

        Q_INVOKABLE void reload();

        StreamingServiceListModel* allServices();
        StreamingServiceProxyListModel* enabledServices();
        StreamingServiceViewModel* currentService() const;
        int currentIndex() const;
        bool isCurrentServiceRunning() const;

        Q_INVOKABLE int webViewIndex(const QString& serviceName) const;

        Q_INVOKABLE void next();
        Q_INVOKABLE void previous();
        Q_INVOKABLE void createService(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                                       const QString& authorWebsite, bool allPlatforms, bool linuxPlatform, bool appImagePlatform,
                                       bool osxPlatform, bool windowsPlatform);

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
        int nextIndex(int index) const;
        int previousIndex(int index) const;

        Application::StreamingServicesController& streamingServices_;
        Application::Players& players_;
        Application::Settings& settings_;
        Application::Setting& currentServiceSetting_;
        Application::IWorkDispatcher& workDispatcher_;
        Application::IStreamingServiceCreator& streamingServiceCreator_;
        Application::ICommandLineParser& commandLineParser_;
        Application::IUserScriptFactory& userScriptFactory_;
        StreamingServiceListModel* allServices_;
        StreamingServiceProxyListModel enabledServices_;
        StreamingServiceViewModel* currentService_ = nullptr;
        int currentIndex_ = -1;
        bool isCurrentServiceRunning_ = false;
    };
}
