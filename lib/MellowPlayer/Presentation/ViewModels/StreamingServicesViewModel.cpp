#include "StreamingServicesViewModel.hpp"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QtWebEngine/QtWebEngine>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesViewModel::StreamingServicesViewModel(PluginManager& pluginManager,
                                                       PlayersService& playersService,
                                                       IApplicationSettings& applicationSettings) :
        QObject(), pluginManager(pluginManager), playersService(playersService),
        applicationSettings(applicationSettings), currentService(nullptr), currentIndex(-1) {

    connect(&pluginManager, &PluginManager::pluginAdded, this, &StreamingServicesViewModel::onPluginAdded);

    for(auto& plugin: pluginManager.getAll()) {
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
    pluginManager.setCurrent(service->getPlugin());
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
    pluginManager.load();
}

void StreamingServicesViewModel::onPluginAdded(Plugin* plugin) {
    model.add(new StreamingServiceModel(*plugin, applicationSettings, playersService, this));
}
