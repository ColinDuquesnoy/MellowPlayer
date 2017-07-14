#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Utils/IWorkDispatcher.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include "StreamingServicesControllerViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StreamingServicesControllerViewModel::StreamingServicesControllerViewModel(
            StreamingServicesController& streamingServices,
            Players& players,
            Settings& settings,
            IWorkDispatcher& workDispatcher,
            IStreamingServiceCreator& streamingServiceCreator,
            ICommandLineParser& commandLineParser) :
        QObject(),
        streamingServices(streamingServices),
        players(players),
        settings(settings),
        currentServiceSetting(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
        workDispatcher(workDispatcher),
        streamingServiceCreator(streamingServiceCreator),
        commandLineParser(commandLineParser),
        allServices(new StreamingServiceListModel(this, QByteArray(), "name")),
        enabledServices(allServices) {

    connect(&streamingServices, &StreamingServicesController::added, this,
            &StreamingServicesControllerViewModel::onServiceAdded);

    for (auto& service: streamingServices.getAll()) {
        onServiceAdded(service.get());
    }
}

void StreamingServicesControllerViewModel::initialize() {
    auto currentServiceName = currentServiceSetting.getValue().toString();
    if (!commandLineParser.getService().isEmpty())
        currentServiceName = commandLineParser.getService();
    for (auto service: allServices->toList()) {
        if (service->getName().toLower() == currentServiceName.toLower())
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

    QModelIndex sourceIndex = allServices->index(allServices->toList().indexOf(service), 0, QModelIndex());

    setCurrentIndex(enabledServices.mapFromSource(sourceIndex).row());
}

void StreamingServicesControllerViewModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    int sourceIndex = enabledServices.mapToSource(enabledServices.index(value, 0, QModelIndex())).row();
    currentIndex = sourceIndex;
    currentService = allServices->at(sourceIndex);

    if (currentService == nullptr) {
        currentServiceSetting.setValue("");
        streamingServices.setCurrent(nullptr);
    }
    else {
        currentServiceSetting.setValue(currentService->getName());
        streamingServices.setCurrent(currentService->getStreamingService());
    }
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
    connect(sv, &StreamingServiceViewModel::isEnabledChanged,
            this, &StreamingServicesControllerViewModel::onServiceEnabledChanged);
    allServices->append(sv);
}

void StreamingServicesControllerViewModel::next() {
    int index = getNextIndex(currentIndex);

    while (index != currentIndex) {
        auto* sv = allServices->at(index);
        if (sv->isRunning()) {
            setCurrentService(sv);
            break;
        }
        index = getNextIndex(index);
    }
}

void StreamingServicesControllerViewModel::previous() {
    int index = getPreviousIndex(currentIndex);

    while (index != currentIndex) {
        auto* sv = allServices->at(index);
        if (sv->isRunning() && sv->isEnabled()) {
            setCurrentService(sv);
            break;
        }
        index = getPreviousIndex(index);
    }
}

void StreamingServicesControllerViewModel::createService(const QString& serviceName, const QString& serviceUrl,
                                                         const QString& authorName, const QString& authorWebsite) {
    workDispatcher.invoke([=]() {
        QString pluginDir = streamingServiceCreator.create(serviceName, serviceUrl, authorName, authorWebsite);
        emit serviceCreated(pluginDir);
        streamingServices.load();
    });
}

int StreamingServicesControllerViewModel::getNextIndex(int index) const {
    int nextIndex = index + 1;
    if (nextIndex >= allServices->count())
        nextIndex = 0;
    return nextIndex;
}

int StreamingServicesControllerViewModel::getPreviousIndex(int index) const {
    int previousIndex = index - 1;
    if (previousIndex < 0)
        previousIndex = allServices->count() - 1;
    return previousIndex;
}

bool StreamingServicesControllerViewModel::getHasRunningServices() const {
    return hasRunningServices;
}

void StreamingServicesControllerViewModel::onPlayerRunningChanged() {
    bool hadRunningServices = hasRunningServices;
    hasRunningServices = false;
    for (int i = 0; i < allServices->count(); ++i) {
        if (allServices->at(i)->isRunning()) {
            hasRunningServices = true;
            break;
        }
    }

    if (hadRunningServices != hasRunningServices) {
        emit hasRunningServicesChanged();
    }
}

int StreamingServicesControllerViewModel::getWebViewIndex(const QString& serviceName) const {
    return allServices->indexOf(serviceName);
}

void StreamingServicesControllerViewModel::onServiceEnabledChanged() {
    if (sender() == currentService) {
        setCurrentIndex(-1);
        emit currentIndexChanged(-1);
    }
}
