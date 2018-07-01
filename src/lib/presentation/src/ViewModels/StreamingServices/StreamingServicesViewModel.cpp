#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/TokenizedFilters.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

StreamingServicesViewModel::StreamingServicesViewModel(StreamingServices& streamingServices,
                                                       Players& players,
                                                       Settings& settings,
                                                       IWorkDispatcher& workDispatcher,
                                                       IStreamingServiceCreator& streamingServiceCreator,
                                                       ICommandLineArguments& commandLineArguments,
                                                       IUserScriptFactory& userScriptFactory,
                                                       IContextProperties& contextProperties,
                                                       INetworkProxies& networkProxies,
                                                       ThemeViewModel& themeViewModel) :
        ContextProperty("_streamingServices", this, contextProperties),
        streamingServices_(streamingServices),
        players_(players),
        settings_(settings),
        currentServiceSetting_(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
        workDispatcher_(workDispatcher),
        streamingServiceCreator_(streamingServiceCreator),
        commandLineArguments_(commandLineArguments),
        userScriptFactory_(userScriptFactory),
        networkProxies_(networkProxies),
        allServices_(new StreamingServiceListModel(this, QByteArray(), "name")),
        enabledServices_(allServices_),
        _themeViewModel(themeViewModel)
{

    connect(&streamingServices, &StreamingServices::added, this, &StreamingServicesViewModel::onServiceAdded);

    for (auto& service : streamingServices.toList()) {
        onServiceAdded(service.get());
    }
}

void StreamingServicesViewModel::initialize()
{
    streamingServices_.load();
    auto currentServiceName = currentServiceSetting_.value().toString();
    if (!commandLineArguments_.service().isEmpty())
        currentServiceName = commandLineArguments_.service();
    for (auto service : allServices_->toList()) {
        if (service->name().toLower() == currentServiceName.toLower())
            setCurrentService(service);
    }
}

StreamingServiceViewModel* StreamingServicesViewModel::currentService() const
{
    return currentService_;
}

void StreamingServicesViewModel::setCurrentService(QObject* value)
{
    if (currentService_ == value)
        return;

    currentService_ = static_cast<StreamingServiceViewModel*>(value);
    if (currentService_ == nullptr) {
        currentServiceSetting_.setValue("");
        streamingServices_.setCurrent(nullptr);
    } else {
        currentServiceSetting_.setValue(currentService_->name());
        streamingServices_.setCurrent(currentService_->streamingService());
    }

    emit currentServiceChanged(currentService_);
}

void StreamingServicesViewModel::reload()
{
    streamingServices_.load();
}

void StreamingServicesViewModel::onServiceAdded(StreamingService* streamingService)
{
    auto* sv = new StreamingServiceViewModel(*streamingService,
                                             settings_.store(),
                                             userScriptFactory_,
                                             players_,
                                             networkProxies_,
                                             _themeViewModel,
                                             this);
    allServices_->append(sv);
}

void StreamingServicesViewModel::next()
{
    int currentIndex = allServices_->indexOf(currentService_);
    int index = nextIndex(currentIndex);

    while (index != currentIndex) {
        auto* sv = allServices_->at(index);
        if (sv->isActive() && sv->isEnabled()) {
            setCurrentService(sv);
            break;
        }
        index = nextIndex(index);
    }
}

void StreamingServicesViewModel::previous()
{
    int currentIndex = allServices_->indexOf(currentService_);
    int index = previousIndex(currentIndex);

    while (index != currentIndex) {
        auto* sv = allServices_->at(index);
        if (sv->isActive() && sv->isEnabled()) {
            setCurrentService(sv);
            break;
        }
        index = previousIndex(index);
    }
}

void StreamingServicesViewModel::createService(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                                                         const QString& authorWebsite,
                                                         bool allPlatforms, bool linuxPlatform, bool appImagePlatform,
                                                         bool osxPlatform, bool windowsPlatform)
{
    QList<Filter> filters;
    if (allPlatforms)
        filters.append(Filter::All);
    else {
        if (linuxPlatform)
            filters.append(Filter::Linux);

        if (appImagePlatform)
            filters.append(Filter::AppImage);

        if (osxPlatform)
            filters.append(Filter::OSX);

        if (windowsPlatform)
            filters.append(Filter::Windows);
    }
    TokenizedFilters tokenizedFilters(filters);
    workDispatcher_.invoke([=]() {
        QString pluginDir = streamingServiceCreator_.create(serviceName, serviceUrl, authorName, authorWebsite, tokenizedFilters.join());
        emit serviceCreated(pluginDir);
        streamingServices_.load();
    });
}

int StreamingServicesViewModel::nextIndex(int index) const
{
    int nextIndex = index + 1;
    if (nextIndex >= allServices_->count())
        nextIndex = 0;
    return nextIndex;
}

int StreamingServicesViewModel::previousIndex(int index) const
{
    int previousIndex = index - 1;
    if (previousIndex < 0)
        previousIndex = allServices_->count() - 1;
    return previousIndex;
}

StreamingServiceListModel* StreamingServicesViewModel::allServices()
{
    return allServices_;
}
StreamingServiceProxyListModel* StreamingServicesViewModel::enabledServices()
{
    return &enabledServices_;
}

void StreamingServicesViewModel::initialize(IQmlApplicationEngine &qmlApplicationEngine) {
    qRegisterMetaType<Infrastructure::NetworkProxy*>("Infrastructure::NetworkProxy*");
    ContextProperty::initialize(qmlApplicationEngine);
}
