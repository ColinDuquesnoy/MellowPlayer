#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicePluginModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ApplicationSettings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PlayerService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, StreamingServicePluginService)
PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)

class QQmlApplicationEngine;
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)

    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
public:
    StreamingServicesModel(UseCases::StreamingServicePluginService& pluginService,
                               UseCases::PlayerService& playerService,
                               UseCases::ApplicationSettings& applicationSettings);
    void initialize();

    Q_INVOKABLE void reload();
    QQmlObjectListModel<StreamingServicePluginModel>* getModel() { return model; }
    QObject* getCurrentService() const;
    int getCurrentIndex() const;

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);

private slots:
    void onPluginAdded(Entities::StreamingServicePlugin* plugin);

private:
    UseCases::StreamingServicePluginService& pluginService;
    UseCases::PlayerService& playerService;
    UseCases::ApplicationSettings& applicationSettings;
    UseCases::Setting& currentServiceSetting;
    QQmlObjectListModel<StreamingServicePluginModel>* model;
    QObject* currentService;
    int currentIndex;
};

END_MELLOWPLAYER_NAMESPACE
