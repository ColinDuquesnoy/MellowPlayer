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
    StreamingServiceModel(UseCases::Plugin& plugin,
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

    UseCases::Plugin* getPlugin() const;

signals:
    void urlChanged(const QString&);

private:
    const QString getCustomUrlSettingsKey() const;

    UseCases::Plugin& plugin;
    UseCases::IApplicationSettings& applicationSettings;
    UseCases::PlayersService& players;
};

using StreamingServiceListModel = ListModel<StreamingServiceModel>;

END_MELLOWPLAYER_NAMESPACE
