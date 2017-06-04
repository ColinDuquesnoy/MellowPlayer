#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Players)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServices)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)

class QQmlApplicationEngine;
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)

    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
public:
    StreamingServicesModel(Application::StreamingServices& streamingServices,
                           Application::Players& players,
                           Application::Settings& settings);
    void initialize();

    Q_INVOKABLE void reload();
    QQmlObjectListModel<StreamingServiceModel>* getModel() { return model; }
    QObject* getCurrentService() const;
    int getCurrentIndex() const;

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);

private slots:
    void onPluginAdded(Application::StreamingService* streamingService);

private:
    Application::StreamingServices& streamingServices;
    Application::Players& players;
    Application::Settings& settings;
    Application::Setting& currentServiceSetting;
    QQmlObjectListModel<StreamingServiceModel>* model;
    QObject* currentService;
    int currentIndex;
};

END_MELLOWPLAYER_NAMESPACE
