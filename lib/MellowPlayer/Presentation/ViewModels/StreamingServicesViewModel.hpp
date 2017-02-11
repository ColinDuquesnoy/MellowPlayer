#pragma once
#include <QObject>
#include <MellowPlayer/Entities.hpp>
#include <MellowPlayer/UseCases.hpp>
#include "../Models/StreamingServicesModel.hpp"

class QQmlApplicationEngine;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesViewModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(StreamingServicesModel* model READ getModel CONSTANT)

    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
public:
    StreamingServicesViewModel(UseCases::StreamingServicesManager& pluginManager, QQmlApplicationEngine* applicationEngine=nullptr);

    Q_INVOKABLE void reload();
    StreamingServicesModel* getModel();
    QObject* getCurrentService() const;
    int getCurrentIndex() const;

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);

private slots:
    void onServiceAdded(Entities::StreamingService* plugin);
    void onServiceRemoved(Entities::StreamingService* plugin);

private:
    UseCases::StreamingServicesManager& streamingServicesManager;
    StreamingServicesModel model;
    QObject* currentService;
    int currentIndex;
};

END_MELLOWPLAYER_NAMESPACE
