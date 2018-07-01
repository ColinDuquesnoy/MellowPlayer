#pragma once

#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>
#include <QObject>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

class QQmlApplicationEngine;

namespace MellowPlayer::Domain
{
    class Settings;
    class Setting;
    class Players;
    class StreamingServices;
    class StreamingService;
    class IWorkDispatcher;
    class IStreamingServiceCreator;
    class IUserScriptFactory;
}

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;
    class INetworkProxies;
}

namespace MellowPlayer::Presentation
{
    class StreamingServicesViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractListModel* allServices READ allServices CONSTANT)
        Q_PROPERTY(QAbstractItemModel* enabledServices READ enabledServices CONSTANT)
        Q_PROPERTY(QObject* currentService READ currentService WRITE setCurrentService NOTIFY currentServiceChanged)
    public:
        StreamingServicesViewModel(Domain::StreamingServices& streamingServices,
                                   Domain::Players& players,
                                   Domain::Settings& settings,
                                   Domain::IWorkDispatcher& workDispatcher,
                                   Domain::IStreamingServiceCreator& streamingServiceCreator,
                                   Infrastructure::ICommandLineArguments& commandLineArguments,
                                   Domain::IUserScriptFactory& userScriptFactory,
                                   IContextProperties& contextProperties,
                                   Infrastructure::INetworkProxies& networkProxies,
                                   ThemeViewModel& themeViewModel);

        using ContextProperty::initialize;
        void initialize();

        Q_INVOKABLE void reload();

        StreamingServiceListModel* allServices();
        StreamingServiceProxyListModel* enabledServices();
        StreamingServiceViewModel* currentService() const;

        Q_INVOKABLE void next();
        Q_INVOKABLE void previous();
        Q_INVOKABLE void createService(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                                       const QString& authorWebsite, bool allPlatforms, bool linuxPlatform, bool appImagePlatform,
                                       bool osxPlatform, bool windowsPlatform);

        void initialize(IQmlApplicationEngine &qmlApplicationEngine) override;

    public slots:
        void setCurrentService(QObject* value);

    signals:
        void currentServiceChanged(QObject* currentService);
        void currentIndexChanged(int currentIndex);
        void serviceCreated(const QString& directory);

    private slots:
        void onServiceAdded(Domain::StreamingService* streamingService);

    private:
        int nextIndex(int index) const;
        int previousIndex(int index) const;

        Domain::StreamingServices& streamingServices_;
        Domain::Players& players_;
        Domain::Settings& settings_;
        Domain::Setting& currentServiceSetting_;
        Domain::IWorkDispatcher& workDispatcher_;
        Domain::IStreamingServiceCreator& streamingServiceCreator_;
        Infrastructure::ICommandLineArguments& commandLineArguments_;
        Domain::IUserScriptFactory& userScriptFactory_;
        Infrastructure::INetworkProxies& networkProxies_;
        StreamingServiceListModel* allServices_;
        StreamingServiceProxyListModel enabledServices_;
        StreamingServiceViewModel* currentService_ = nullptr;
        ThemeViewModel& _themeViewModel;
    };
}
