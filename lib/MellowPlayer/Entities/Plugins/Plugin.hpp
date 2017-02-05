#pragma once

#include <memory>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Logging.hpp>
#include "PluginMetadata.hpp"
#include "PluginScript.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class Plugin: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author READ getAuthor CONSTANT);
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT);
    Q_PROPERTY(QString toolbarColor READ getToolbarColor CONSTANT);
    Q_PROPERTY(QString logo READ getLogo CONSTANT);
    Q_PROPERTY(QString name READ getName CONSTANT);
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged);
    Q_PROPERTY(QString version READ getVersion CONSTANT);
    Q_PROPERTY(PluginScript* script READ getScriptPtr CONSTANT);
public:
    Plugin(const PluginMetadata& metadata);

    bool isValid() const;

    const QString& getAuthor() const;
    const QString& getAuthorWebsite() const;
    QString getToolbarColor() const;
    QString getLogo() const;
    const QString& getName() const;
    QString getUrl() const;
    const QString& getVersion() const;
    PluginScript& getScript();
    PluginScript* getScriptPtr();

    void setCustomUrl(const QString& url);

    bool operator==(const Plugin& rhs) const;
    bool operator!=(const Plugin& rhs) const;

signals:
    void urlChanged(QString);

private:
    const QString getCustomUrlSettingsKey() const;

    Logging::ILogger& logger;
    PluginMetadata metadata;
    std::unique_ptr<PluginScript> script;
};


using PluginList = QList<std::shared_ptr<MellowPlayer::Entities::Plugin>>;

END_MELLOWPLAYER_NAMESPACE

