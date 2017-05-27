#pragma once

#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ISettingsProvider)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Player)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PlayerService)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicePluginModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString color READ getColor CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(UseCases::Player* player READ getPlayer CONSTANT)
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString version READ getVersion CONSTANT)
    Q_PROPERTY(QString authorName READ getAuthorName CONSTANT)
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
public:
    StreamingServicePluginModel(Entities::StreamingServicePlugin& plugin,
                                UseCases::ISettingsProvider& settings,
                                UseCases::PlayerService& playerManager,
                                QObject* parent= nullptr);

    QString getColor() const;
    QString getLogo() const;
    QString getName() const;
    UseCases::Player* getPlayer();
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
    UseCases::ISettingsProvider& settingsProvider;
    UseCases::PlayerService& players;
};

END_MELLOWPLAYER_NAMESPACE
