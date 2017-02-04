#pragma once

#include <MellowPlayer/Macros.hpp>
#include <QtCore/QString>
#include <QtGui/QImage>
#include "PluginMetadata.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class Plugin {
public:
    Plugin(const PluginMetadata& metadata);

    const QString& getAuthor() const;
    const QString& getAuthorWebsite() const;
    QString getToolbarColor() const;
    QImage getLogo() const;
    const QString& getName() const;
    QString getUrl() const;
    const QString& getVersion() const;
    const QString& getScript() const;  // todo return a PluginScript

    bool isValid() const;

    bool operator==(const Plugin& rhs) const {
        return getName() == rhs.getName() && getUrl() == rhs.getUrl();
    }

    void setCustomUrl(const QString& url);


private:
    const QString getCustomUrlSettingsKey() const;

    PluginMetadata metadata;
};


using PluginList = QList<MellowPlayer::Entities::Plugin>;

END_MELLOWPLAYER_NAMESPACE

