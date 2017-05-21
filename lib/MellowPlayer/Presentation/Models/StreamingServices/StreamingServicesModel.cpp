#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/UseCases/Settings/ApplicationSettings.hpp>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/UseCases/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include "StreamingServicesModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesModel::StreamingServicesModel(StreamingServicePluginService& pluginService,
                                               PlayerService& playerService,
                                               ApplicationSettings& applicationSettings) :
        QObject(), pluginService(pluginService), playerService(playerService),
        applicationSettings(applicationSettings),
        currentServiceSetting(applicationSettings.getSetting("private/current-service")),
        model(new QQmlObjectListModel<StreamingServicePluginModel>(this)),
        currentService(nullptr), currentIndex(-1) {

    connect(&pluginService, &StreamingServicePluginService::pluginAdded, this, &StreamingServicesModel::onPluginAdded);

    for (auto& plugin: pluginService.getAll()) {
        onPluginAdded(plugin.get());
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

    auto service = static_cast<StreamingServicePluginModel*>(value);
    currentServiceSetting.setValue(value->property("name").toString());
    currentService = value;
    pluginService.setCurrent(service->getPlugin());
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
    pluginService.load();
}

void StreamingServicesModel::onPluginAdded(StreamingServicePlugin* plugin) {
    model->append(new StreamingServicePluginModel(
            *plugin, applicationSettings.getSettingsProvider(), playerService, this));
}
