#pragma once

#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ISettingsProvider)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Player)
PREDECLARE_MELLOWPLAYER_CLASS(Application, PlayerService)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicePluginModel: public QObject
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
    StreamingServicePluginModel(Entities::StreamingServicePlugin& plugin,
                                Application::ISettingsProvider& settings,
                                Application::PlayerService& playerManager,
                                QObject* parent= nullptr);

    QString getColor() const;
    QString getLogo() const;
    QString getName() const;
    Application::Player* getPlayer();
    QString getUrl() const;
    QString getVersion() const;
    QString getAuthorName() const;
    QString getAuthorWebsite() const;

    bool operator==(const StreamingServicePluginModel& rhs) const;
    bool operator!=(const StreamingServicePluginModel& rhs) const;

    Entities::StreamingServicePlugin* getPlugin() const;

public slots:
    void setUrl(const QString& url);

signals:
    void urlChanged(const QString&);

private:
    const QString getCustomUrlSettingsKey() const;

    Entities::StreamingServicePlugin& plugin;
    Application::ISettingsProvider& settingsProvider;
    Application::PlayerService& players;
};

END_MELLOWPLAYER_NAMESPACE
