#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include "StreamingServicesModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesModel::StreamingServicesModel(StreamingServices& streamingServices,
                                               Players& players,
                                               Settings& settings) :
        QObject(), streamingServices(streamingServices), players(players),
        settings(settings),
        currentServiceSetting(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
        model(new QQmlObjectListModel<StreamingServiceModel>(this)),
        currentService(nullptr), currentIndex(-1) {

    connect(&streamingServices, &StreamingServices::added, this, &StreamingServicesModel::onServiceAdded);

    for (auto& service: streamingServices.getAll()) {
        onServiceAdded(service.get());
    }
}

void StreamingServicesModel::initialize() {
    auto currentServiceName = currentServiceSetting.getValue().toString();
    for (auto service: model->toList()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }
}

QObject* StreamingServicesModel::getCurrentService() const {
    return currentService;
}

int StreamingServicesModel::getCurrentIndex() const {
    return currentIndex;
}

void StreamingServicesModel::setCurrentService(QObject* value) {
    if (currentService == value)
        return;

    auto service = static_cast<StreamingServiceModel*>(value);
    currentServiceSetting.setValue(value->property("name").toString());
    currentService = value;
    streamingServices.setCurrent(service->getStreamingService());
    setCurrentIndex(model->toList().indexOf(service));
    emit currentServiceChanged(currentService);
}

void StreamingServicesModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    currentIndex = value;
    emit currentIndexChanged(currentIndex);
}

void StreamingServicesModel::reload() {
    streamingServices.load();
}

void StreamingServicesModel::onServiceAdded(StreamingService* streamingService) {
    model->append(new StreamingServiceModel(
            *streamingService, settings.getSettingsProvider(), players, this));
}
