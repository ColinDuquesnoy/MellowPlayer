#pragma once

#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ISettingsProvider)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Player)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Players)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServiceModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString color READ getColor CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(Application::Player* player READ getPlayer CONSTANT)
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString version READ getVersion CONSTANT)
    Q_PROPERTY(QString authorName READ getAuthorName CONSTANT)
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
public:
    StreamingServiceModel(Application::StreamingService& streamingService,
                          Application::ISettingsProvider& settings,
                          Application::Players& players,
                          QObject* parent= nullptr);

    QString getColor() const;
    QString getLogo() const;
    QString getName() const;
    Application::Player* getPlayer();
    QString getUrl() const;
    QString getVersion() const;
    QString getAuthorName() const;
    QString getAuthorWebsite() const;

    bool operator==(const StreamingServiceModel& rhs) const;
    bool operator!=(const StreamingServiceModel& rhs) const;

    Application::StreamingService* getPlugin() const;

public slots:
    void setUrl(const QString& url);

signals:
    void urlChanged(const QString&);

private:
    const QString getCustomUrlSettingsKey() const;

    Application::StreamingService& streamingService;
    Application::ISettingsProvider& settingsProvider;
    Application::Players& players;
};

END_MELLOWPLAYER_NAMESPACE
