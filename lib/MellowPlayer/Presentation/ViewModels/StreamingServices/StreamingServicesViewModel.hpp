#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Players)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServices)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)

class QQmlApplicationEngine;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesViewModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)
    Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(bool hasRunningServices READ getHasRunningServices NOTIFY hasRunningServicesChanged)
public:
    StreamingServicesViewModel(Application::StreamingServices& streamingServices,
                           Application::Players& players,
                           Application::Settings& settings);
    void initialize();

    Q_INVOKABLE void reload();
    StreamingServiceListModel* getModel() { return model; }
    StreamingServiceViewModel* getCurrentService() const;
    int getCurrentIndex() const;
    bool getHasRunningServices() const;

    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();

public slots:
    void setCurrentService(QObject* value);
    void setCurrentIndex(int value);

signals:
    void currentServiceChanged(QObject* currentService);
    void currentIndexChanged(int currentIndex);
    void hasRunningServicesChanged();

private slots:
    void onServiceAdded(Application::StreamingService* streamingService);
    void onPlayerRunningChanged();

private:
    int getNextIndex(int index) const;
    int getPreviousIndex(int index) const;

    Application::StreamingServices& streamingServices;
    Application::Players& players;
    Application::Settings& settings;
    Application::Setting& currentServiceSetting;
    StreamingServiceListModel* model;
    StreamingServiceViewModel* currentService;
    int currentIndex;
    bool hasRunningServices = false;
};

END_MELLOWPLAYER_NAMESPACE
