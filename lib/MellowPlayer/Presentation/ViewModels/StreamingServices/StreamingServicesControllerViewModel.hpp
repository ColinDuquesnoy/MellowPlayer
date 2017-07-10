#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>

class QQmlApplicationEngine;
namespace MellowPlayer::Application {

    class Settings;
    class Setting;
    class Players;
    class StreamingServicesController;
    class StreamingService;
    class IWorkDispatcher;
    class IStreamingServiceCreator;

}

namespace MellowPlayer::Presentation {

    class StreamingServicesControllerViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)
        Q_PROPERTY(QObject* currentService READ getCurrentService WRITE setCurrentService NOTIFY currentServiceChanged)
        Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
        Q_PROPERTY(bool hasRunningServices READ getHasRunningServices NOTIFY hasRunningServicesChanged)
    public:
        StreamingServicesControllerViewModel(Application::StreamingServicesController& streamingServices,
                                   Application::Players& players,
                                   Application::Settings& settings,
                                   Application::IWorkDispatcher& workDispatcher,
                                   Application::IStreamingServiceCreator& streamingServiceCreator);
        void initialize();

        Q_INVOKABLE void reload();
        StreamingServiceListModel* getModel() { return model; }
        StreamingServiceViewModel* getCurrentService() const;
        int getCurrentIndex() const;
        bool getHasRunningServices() const;

        Q_INVOKABLE void next();
        Q_INVOKABLE void previous();
        Q_INVOKABLE void createService(const QString& serviceName, const QString& serviceUrl, const QString& authorName, const QString& authorWebsite);

    public slots:
        void setCurrentService(QObject* value);
        void setCurrentIndex(int value);

    signals:
        void currentServiceChanged(QObject* currentService);
        void currentIndexChanged(int currentIndex);
        void hasRunningServicesChanged();
        void serviceCreated(const QString& directory);

    private slots:
        void onServiceAdded(Application::StreamingService* streamingService);
        void onPlayerRunningChanged();

    private:
        int getNextIndex(int index) const;
        int getPreviousIndex(int index) const;

        Application::StreamingServicesController& streamingServices;
        Application::Players& players;
        Application::Settings& settings;
        Application::Setting& currentServiceSetting;
        Application::IWorkDispatcher& workDispatcher;
        Application::IStreamingServiceCreator& streamingServiceCreator;
        StreamingServiceListModel* model;
        StreamingServiceViewModel* currentService = nullptr;
        int currentIndex = -1;
        bool hasRunningServices = false;
    };

}
