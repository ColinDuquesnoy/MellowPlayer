#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/UseCases/Interfaces/IApplicationSettings.hpp>
#include <MellowPlayer/UseCases/Services/PluginService.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include "StreamingServicesViewModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesViewModel::StreamingServicesViewModel(PluginService& pluginService,
                                                       PlayerService& playerService,
                                                       IApplicationSettings& applicationSettings) :
        QObject(), pluginService(pluginService), playerService(playerService),
        applicationSettings(applicationSettings), currentService(nullptr), currentIndex(-1) {

    connect(&pluginService, &PluginService::pluginAdded, this, &StreamingServicesViewModel::onPluginAdded);

    for(auto& plugin: pluginService.getAll()) {
        onPluginAdded(plugin.get());
    }
}

void StreamingServicesViewModel::initialize() {
    auto currentServiceName = applicationSettings.getCurrentService();
    qDebug() << currentServiceName;
    for (auto service: model.getItems()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }
}

StreamingServiceListModel* StreamingServicesViewModel::getModel() {
    return &model;
}

QObject* StreamingServicesViewModel::getCurrentService() const {
    return currentService;
}

int StreamingServicesViewModel::getCurrentIndex() const {
    return currentIndex;
}

void StreamingServicesViewModel::setCurrentService(QObject* value) {
    if (currentService == value)
        return;

    auto service = static_cast<StreamingServiceModel*>(value);
    applicationSettings.setCurrentService(value->property("name").toString());
    currentService = value;
    pluginService.setCurrent(service->getPlugin());
    setCurrentIndex(model.getItems().indexOf(service));
    emit currentServiceChanged(currentService);
}

void StreamingServicesViewModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    currentIndex = value;
    emit currentIndexChanged(currentIndex);
}

void StreamingServicesViewModel::reload() {
    pluginService.load();
}

void StreamingServicesViewModel::onPluginAdded(Plugin* plugin) {
    model.append(new StreamingServiceModel(*plugin, applicationSettings, playerService, this));
}
