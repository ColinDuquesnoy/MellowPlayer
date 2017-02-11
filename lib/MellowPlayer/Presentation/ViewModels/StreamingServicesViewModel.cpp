#include "StreamingServicesViewModel.hpp"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QDebug>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesViewModel::StreamingServicesViewModel(StreamingServicesManager& pluginManager,
                                                       QQmlApplicationEngine* applicationEngine)
    :
    QObject(), streamingServicesManager(pluginManager), currentService(nullptr), currentIndex(-1) {

    if (applicationEngine != nullptr) {
        applicationEngine->rootContext()->setContextProperty("streamingServices", this);
    }

    connect(&pluginManager, &StreamingServicesManager::serviceAdded,
            this, &StreamingServicesViewModel::onServiceAdded);
    connect(&pluginManager, &StreamingServicesManager::serviceRemoved,
            this, &StreamingServicesViewModel::onServiceRemoved);

    reload();

    QSettings settings;
    auto currentServiceName = settings.value("currentService", "").toString();
    qDebug() << currentServiceName;
    for (auto service: model.getServices()) {
        if (service->getName() == currentServiceName)
            setCurrentService(service);
    }

}

StreamingServicesModel* StreamingServicesViewModel::getModel() {
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

    auto service = static_cast<StreamingService*>(value);
    QSettings settings;
    settings.setValue("currentService", value->property("name").toString());
    currentService = value;
    streamingServicesManager.setCurrentService(service);
    setCurrentIndex(model.getServices().indexOf(service));
    emit currentServiceChanged(currentService);

}

void StreamingServicesViewModel::setCurrentIndex(int value) {
    if (currentIndex == value)
        return;

    currentIndex = value;
    emit currentIndexChanged(currentIndex);
}

void StreamingServicesViewModel::reload() {
    streamingServicesManager.load();
}

void StreamingServicesViewModel::onServiceAdded(StreamingService* plugin) {
    model.addService(plugin);
}

void StreamingServicesViewModel::onServiceRemoved(StreamingService* plugin) {
    model.removeService(plugin);
}
