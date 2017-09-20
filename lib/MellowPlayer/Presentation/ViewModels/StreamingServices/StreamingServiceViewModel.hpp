#pragma once

#include <QtCore/QObject>
#include <memory>

namespace MellowPlayer::Application
{
    class StreamingService;
    class ISettingsProvider;
    class Player;
    class Players;
}

namespace MellowPlayer::Presentation
{
    class StreamingServiceViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString logo READ logo CONSTANT)
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(Application::Player* player READ player CONSTANT)
        Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(QString version READ version CONSTANT)
        Q_PROPERTY(QString authorName READ authorName CONSTANT)
        Q_PROPERTY(QString authorWebsite READ authorWebsite CONSTANT)
        Q_PROPERTY(bool isEnabled READ isEnabled WRITE setEnabled NOTIFY isEnabledChanged)
        Q_PROPERTY(int sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
        Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    public:
        StreamingServiceViewModel(Application::StreamingService& streamingService, Application::ISettingsProvider& settings,
                                  Application::Players& players, QObject* parent = nullptr);

        QString logo() const;
        QString name() const;
        Application::Player* player();
        QString url() const;
        QString version() const;
        QString authorName() const;
        QString authorWebsite() const;
        bool isRunning() const;

        bool operator==(const StreamingServiceViewModel& rhs) const;
        bool operator!=(const StreamingServiceViewModel& rhs) const;

        Application::StreamingService* streamingService() const;

        int sortOrder() const;
        void setSortOrder(int newOrder);

        bool isEnabled() const;
        void setEnabled(bool enabled);

    public slots:
        void setUrl(const QString& newUrl);

    signals:
        void urlChanged(const QString&);
        void sortOrderChanged();
        void isEnabledChanged();
        void isRunningChanged();

    private:
        QString customUrlSettingsKey() const;
        QString sortOrderSettingsKey() const;
        QString isEnabledSettingsKey() const;

        Application::StreamingService& streamingService_;
        Application::ISettingsProvider& settingsProvider_;
        std::shared_ptr<Application::Player> player_;
    };
}
