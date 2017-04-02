#pragma once

#include <MellowPlayer/Macros.hpp>
#include "ListModel.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Plugin)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IApplicationSettings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Player)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PlayersService)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServiceModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString color READ getColor CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(UseCases::Player* player READ getPlayer CONSTANT)
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
public:
    StreamingServiceModel(Entities::Plugin& plugin,
                          UseCases::IApplicationSettings& applicationSettings,
                          UseCases::PlayersService& playerManager,
                          QObject* parent= nullptr);

    QString getColor() const;
    QString getLogo() const;
    QString getName() const;
    UseCases::Player* getPlayer();
    QString getUrl() const;
    Q_INVOKABLE void setCustomUrl(const QString& url);

    bool operator==(const StreamingServiceModel& rhs) const;
    bool operator!=(const StreamingServiceModel& rhs) const;

    Entities::Plugin* getPlugin() const;

signals:
    void urlChanged(const QString&);

private:
    const QString getCustomUrlSettingsKey() const;

    Entities::Plugin& plugin;
    UseCases::IApplicationSettings& applicationSettings;
    UseCases::PlayersService& players;
};

using StreamingServiceListModel = ListModel<StreamingServiceModel>;

END_MELLOWPLAYER_NAMESPACE
