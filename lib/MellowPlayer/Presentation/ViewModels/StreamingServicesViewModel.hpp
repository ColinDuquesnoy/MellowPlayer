#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Models/StreamingServiceModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IApplicationSettings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PlayersService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PluginManager)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Plugin)

class QQmlApplicationEngine;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesViewModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)

    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
public:
    StreamingServicesViewModel(UseCases::PluginManager& pluginManager,
                               UseCases::PlayersService& playersService,
                               UseCases::IApplicationSettings& applicationSettings);
    void initialize();

    Q_INVOKABLE void reload();
    StreamingServiceListModel* getModel();
    QObject* getCurrentService() const;
    int getCurrentIndex() const;

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);

private slots:
    void onPluginAdded(UseCases::Plugin* plugin);

private:
    UseCases::PluginManager& pluginManager;
    UseCases::PlayersService& playersService;
    UseCases::IApplicationSettings& applicationSettings;
    StreamingServiceListModel model;
    QObject* currentService;
    QObject* currentPlayer;
    int currentIndex;
};

END_MELLOWPLAYER_NAMESPACE
