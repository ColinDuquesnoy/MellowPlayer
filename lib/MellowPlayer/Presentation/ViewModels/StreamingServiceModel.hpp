#pragma once

#include <MellowPlayer/UseCases.hpp>
#include "ListModel.hpp"

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
                          UseCases::PlayersManager& playerManager,
                          QObject* parent= nullptr);

    QString getColor() const { return plugin.getColor(); }
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
    UseCases::PlayersManager& players;
};

using StreamingServiceListModel = ListModel<StreamingServiceModel>;

END_MELLOWPLAYER_NAMESPACE
