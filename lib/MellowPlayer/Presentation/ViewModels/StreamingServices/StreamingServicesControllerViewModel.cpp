#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Utils/IWorkDispatcher.hpp>
#include "StreamingServicesControllerViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StreamingServicesControllerViewModel::StreamingServicesControllerViewModel(StreamingServicesController& streamingServices,
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

    connect(&streamingServices, &StreamingServicesController::added, this, &StreamingServicesControllerViewModel::onServiceAdded);

    for (auto& service: streamingServices.getAll()) {
        onServiceAdded(service.get());
    }
}

void StreamingServicesControllerViewModel::initialize() {
    auto currentServiceName = currentServiceSetting.getValue().toString();
    for (auto service: model->toList()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }
}

StreamingServiceViewModel* StreamingServicesControllerViewModel::getCurrentService() const {
    return currentService;
}

int StreamingServicesControllerViewModel::getCurrentIndex() const {
    return currentIndex;
}

void StreamingServicesControllerViewModel::setCurrentService(QObject* value) {
    if (currentService == value)
        return;

    auto service = static_cast<StreamingServiceViewModel*>(value);
    setCurrentIndex(model->toList().indexOf(service));
}

void StreamingServicesControllerViewModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    currentIndex = value;
    currentService = model->at(currentIndex);

    currentServiceSetting.setValue(currentService->getName());
    streamingServices.setCurrent(currentService->getStreamingService());
    emit currentIndexChanged(currentIndex);
    emit currentServiceChanged(currentService);
}

void StreamingServicesControllerViewModel::reload() {
    streamingServices.load();
}

void StreamingServicesControllerViewModel::onServiceAdded(StreamingService* streamingService) {
    auto* sv = new StreamingServiceViewModel(*streamingService, settings.getSettingsProvider(), players, this);
    Player* player = sv->getPlayer();
    connect(player, &Player::isRunningChanged, this, &StreamingServicesControllerViewModel::onPlayerRunningChanged);
    model->append(sv);
}

void StreamingServicesControllerViewModel::next() {
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

void StreamingServicesControllerViewModel::previous() {
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

void StreamingServicesControllerViewModel::createService(const QString &serviceName, const QString &serviceUrl,
                                               const QString &authorName, const QString &authorWebsite)
{
    workDispatcher.invoke([=]() {
        QString pluginDir = streamingServiceCreator.create(serviceName, serviceUrl, authorName, authorWebsite);
        emit serviceCreated(pluginDir);
        streamingServices.load();
    });
}

int StreamingServicesControllerViewModel::getNextIndex(int index) const {
    int nextIndex = index + 1;
    if (nextIndex >= model->count())
        nextIndex = 0;
    return nextIndex;
}

int StreamingServicesControllerViewModel::getPreviousIndex(int index) const {
    int previousIndex = index - 1;
    if (previousIndex < 0)
        previousIndex = model->count() - 1;
    return previousIndex;
}

bool StreamingServicesControllerViewModel::getHasRunningServices() const {
    return hasRunningServices;
}

void StreamingServicesControllerViewModel::onPlayerRunningChanged() {
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
