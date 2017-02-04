#include "Plugin.hpp"
#include <QtGui/QIcon>
#include <QtCore/QSettings>

USE_MELLOWPLAYER_NAMESPACE(Entities)

Plugin::Plugin(const PluginMetadata &metadata): metadata(metadata) {

}

const QString &Plugin::getAuthor() const {
    return metadata.author;
}

const QString &Plugin::getAuthorWebsite() const {
    return metadata.authorWebsite;
}

QString Plugin::getToolbarColor() const {
    if(QColor(metadata.color).isValid())
        return metadata.color;
    return "";
}

QImage Plugin::getLogo() const {
    return QIcon(metadata.logoPath).pixmap(64, 64).toImage();
}

const QString &Plugin::getName() const {
    return metadata.name;
}

QString Plugin::getUrl() const {
    QSettings settings;
    QString customUrl = settings.value(getCustomUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? metadata.url : customUrl;
}

const QString Plugin::getCustomUrlSettingsKey() const { return metadata.name + "/url"; }

const QString &Plugin::getVersion() const {
    return metadata.version;
}

const QString &Plugin::getScript() const {
    return metadata.script;
}

bool Plugin::isValid() const {
    return metadata.isValid();
}

void Plugin::setCustomUrl(const QString &url) {
    QSettings settings;
    settings.setValue(getCustomUrlSettingsKey(), url);

}
