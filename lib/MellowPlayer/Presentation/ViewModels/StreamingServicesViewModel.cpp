#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>
#include <MellowPlayer/UseCases/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/UseCases/Services/PluginService.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include "StreamingServicesViewModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesViewModel::StreamingServicesViewModel(PluginService& pluginService,
                                                       PlayerService& playerService,
                                                       ISettingsProvider& applicationSettings) :
        QObject(), pluginService(pluginService), playerService(playerService),
        applicationSettings(applicationSettings), model(new QQmlObjectListModel<StreamingServiceModel>(this)),
        currentService(nullptr), currentIndex(-1) {

    connect(&pluginService, &PluginService::pluginAdded, this, &StreamingServicesViewModel::onPluginAdded);

    for(auto& plugin: pluginService.getAll()) {
        onPluginAdded(plugin.get());
    }
}

void StreamingServicesViewModel::initialize() {
    auto currentServiceName = applicationSettings.getCurrentService();
    for (auto service: model->toList()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }
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
    setCurrentIndex(model->toList().indexOf(service));
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
    model->append(new StreamingServiceModel(*plugin, applicationSettings, playerService, this));
}
