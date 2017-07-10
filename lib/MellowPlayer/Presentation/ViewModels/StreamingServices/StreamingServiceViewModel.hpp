#pragma once

namespace MellowPlayer::Application {

    class StreamingService;
    class ISettingsProvider;
    class Player;
    class Players;

}

namespace MellowPlayer::Presentation {

    class StreamingServiceViewModel: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString logo READ getLogo CONSTANT)
        Q_PROPERTY(QString name READ getName CONSTANT)
        Q_PROPERTY(Application::Player* player READ getPlayer CONSTANT)
        Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(QString version READ getVersion CONSTANT)
        Q_PROPERTY(QString authorName READ getAuthorName CONSTANT)
        Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
    public:
        StreamingServiceViewModel(Application::StreamingService& streamingService,
                              Application::ISettingsProvider& settings,
                              Application::Players& players,
                              QObject* parent= nullptr);

        QString getLogo() const;
        QString getName() const;
        Application::Player* getPlayer();
        QString getUrl() const;
        QString getVersion() const;
        QString getAuthorName() const;
        QString getAuthorWebsite() const;
        bool isRunning() const;

        bool operator==(const StreamingServiceViewModel& rhs) const;
        bool operator!=(const StreamingServiceViewModel& rhs) const;

        Application::StreamingService* getStreamingService() const;

    public slots:
        void setUrl(const QString& url);

    signals:
        void urlChanged(const QString&);

    private:
        const QString getCustomUrlSettingsKey() const;

        Application::StreamingService& streamingService;
        Application::ISettingsProvider& settingsProvider;
        Application::Players& players;
        bool isCurrent_ = false;
    };

}
