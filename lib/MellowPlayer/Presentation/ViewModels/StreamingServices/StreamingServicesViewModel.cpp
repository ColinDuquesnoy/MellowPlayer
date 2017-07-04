#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Utils/IWorkDispatcher.hpp>
#include "StreamingServicesViewModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesViewModel::StreamingServicesViewModel(StreamingServices& streamingServices,
                                               Players& players,
                                               Settings& settings,
                                               IWorkDispatcher& workDispatcher,
                                               IStreamingServiceCreator& streamingServiceCreator) :
        QObject(), streamingServices(streamingServices), players(players),
        settings(settings),
        currentServiceSetting(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
        workDispatcher(workDispatcher),
        streamingServiceCreator(streamingServiceCreator),
        model(new StreamingServiceListModel(this)) {

    connect(&streamingServices, &StreamingServices::added, this, &StreamingServicesViewModel::onServiceAdded);

    for (auto& service: streamingServices.getAll()) {
        onServiceAdded(service.get());
    }
}

void StreamingServicesViewModel::initialize() {
    auto currentServiceName = currentServiceSetting.getValue().toString();
    for (auto service: model->toList()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }
}

StreamingServiceViewModel* StreamingServicesViewModel::getCurrentService() const {
    return currentService;
}

int StreamingServicesViewModel::getCurrentIndex() const {
    return currentIndex;
}

void StreamingServicesViewModel::setCurrentService(QObject* value) {
    if (currentService == value)
        return;

    auto service = static_cast<StreamingServiceViewModel*>(value);
    setCurrentIndex(model->toList().indexOf(service));
}

void StreamingServicesViewModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    currentIndex = value;
    currentService = model->at(currentIndex);

    currentServiceSetting.setValue(currentService->getName());
    streamingServices.setCurrent(currentService->getStreamingService());
    emit currentIndexChanged(currentIndex);
    emit currentServiceChanged(currentService);
}

void StreamingServicesViewModel::reload() {
    streamingServices.load();
}

void StreamingServicesViewModel::onServiceAdded(StreamingService* streamingService) {
    auto* sv = new StreamingServiceViewModel(*streamingService, settings.getSettingsProvider(), players, this);
    Player* player = sv->getPlayer();
    connect(player, &Player::isRunningChanged, this, &StreamingServicesViewModel::onPlayerRunningChanged);
    model->append(sv);
}

void StreamingServicesViewModel::next() {
    int index = getNextIndex(currentIndex);

    while(index != currentIndex) {
        auto* sv = model->at(index);
        if (sv->isRunning()) {
            setCurrentIndex(index);
            break;
        }
        index = getNextIndex(index);
    }
}

void StreamingServicesViewModel::previous() {
    int index = getPreviousIndex(currentIndex);

    while(index != currentIndex) {
        auto* sv = model->at(index);
        if (sv->isRunning()) {
            setCurrentIndex(index);
            break;
        }
        index = getPreviousIndex(index);
    }
}

void StreamingServicesViewModel::createService(const QString &serviceName, const QString &serviceUrl,
                                               const QString &authorName, const QString &authorWebsite)
{
    workDispatcher.invoke([=]() {
        QString pluginDir = streamingServiceCreator.create(serviceName, serviceUrl, authorName, authorWebsite);
        emit serviceCreated(pluginDir);
        streamingServices.load();
    });
}

int StreamingServicesViewModel::getNextIndex(int index) const {
    int nextIndex = index + 1;
    if (nextIndex >= model->count())
        nextIndex = 0;
    return nextIndex;
}

int StreamingServicesViewModel::getPreviousIndex(int index) const {
    int previousIndex = index - 1;
    if (previousIndex < 0)
        previousIndex = model->count() - 1;
    return previousIndex;
}

bool StreamingServicesViewModel::getHasRunningServices() const {
    return hasRunningServices;
}

void StreamingServicesViewModel::onPlayerRunningChanged() {
    bool hadRunningServices = hasRunningServices;
    hasRunningServices = false;
    for(int i = 0; i < model->count(); ++i)  {
        if (model->at(i)->isRunning()) {
            hasRunningServices = true;
            break;
        }
    }

    if (hadRunningServices != hasRunningServices) {
        emit hasRunningServicesChanged();
    }
}
