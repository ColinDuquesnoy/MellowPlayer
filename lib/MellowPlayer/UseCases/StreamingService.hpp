#pragma once

#include <memory>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Logging.hpp>
#include <MellowPlayer/Entities.hpp>
#include "IApplicationSettings.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class Player;

class StreamingService: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author READ getAuthor CONSTANT)
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
    Q_PROPERTY(QString toolbarColor READ getToolbarColor CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
    Q_PROPERTY(QString version READ getVersion CONSTANT)
    Q_PROPERTY(Player* player READ getPlayer CONSTANT)
    Q_PROPERTY(Entities::PluginScript* script READ getScript CONSTANT)
public:
    StreamingService(const Entities::PluginMetadata& metadata, IApplicationSettings& applicationSettings);
    ~StreamingService();
    bool isValid() const;

    const QString& getAuthor() const;
    const QString& getAuthorWebsite() const;
    QString getToolbarColor() const;
    QString getLogo() const;
    const QString& getName() const;
    QString getUrl() const;
    const QString& getVersion() const;

    Entities::PluginScript* getScript();
    Player* getPlayer();

    Q_INVOKABLE void setCustomUrl(const QString& url);

    bool operator==(const StreamingService& rhs) const;
    bool operator!=(const StreamingService& rhs) const;

signals:
    void urlChanged(QString);

private:
    const QString getCustomUrlSettingsKey() const;

    Logging::ILogger& logger;
    Entities::PluginMetadata metadata;
    IApplicationSettings& applicationSettings;
    std::unique_ptr<Entities::PluginScript> script;
    std::unique_ptr<Player> player;
};


using StreamingServicesList = QList<std::shared_ptr<MellowPlayer::UseCases::StreamingService>>;

END_MELLOWPLAYER_NAMESPACE

