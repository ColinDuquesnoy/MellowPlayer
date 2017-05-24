#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/UseCases/Services/StreamingServicePluginService.hpp>
#include "StreamingServiceStyleModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServiceStyleModel::StreamingServiceStyleModel(StreamingServicePluginService& pluginService) :
        usePluginStyle(true),
        style(StreamingServiceStyle::defaultStyle()),
        pluginService(pluginService) {
    connect(&pluginService, &StreamingServicePluginService::currentPluginChanged, this, &StreamingServiceStyleModel::onPluginChanged);
}

QString StreamingServiceStyleModel::getTheme() const {
    return style.theme.toLower();
}

QString StreamingServiceStyleModel::getAccent() const {
    return style.accent;
}

QString StreamingServiceStyleModel::getBackground() const {
    return style.background;
}

QString StreamingServiceStyleModel::getForeground() const {
    return style.foreground;
}

QString StreamingServiceStyleModel::getPrimary() const {
    return style.primary;
}

QString StreamingServiceStyleModel::getPrimaryForeground() const {
    return style.primaryForeground;
}

QString StreamingServiceStyleModel::getSecondary() const {
    return style.secondary;
}

QString StreamingServiceStyleModel::getSecondaryForeground() const {
    return style.secondaryForeground;
}

bool StreamingServiceStyleModel::getUsePluginStyle() const {
    return usePluginStyle;
}

void StreamingServiceStyleModel::setUsePluginStyle(bool value) {
    if (value == usePluginStyle)
        return;

    usePluginStyle = value;
    emit usePluginStyleChanged();

    StreamingServicePlugin* currentPlugin = pluginService.getCurrent();
    if (usePluginStyle && currentPlugin != nullptr)
        updateStyle(currentPlugin->getStyle());
    else
        updateStyle(StreamingServiceStyle::defaultStyle());
}

void StreamingServiceStyleModel::onPluginChanged(StreamingServicePlugin* plugin) {
    if (plugin != nullptr)
        updateStyle(plugin->getStyle());
}

void StreamingServiceStyleModel::setTheme(const QString& value) {
    if (value == style.theme)
        return;

    style.theme = value;
    emit themeChanged();
}

void StreamingServiceStyleModel::setAccent(const QString& value) {
    if (value == style.accent)
        return;

    style.accent = value;
    emit accentChanged();
}

void StreamingServiceStyleModel::setBackground(const QString& value) {
    if (value == style.background)
        return;

    style.background = value;
    emit backgroundChanged();
}

void StreamingServiceStyleModel::setForeground(const QString& value) {
    if (value == style.foreground)
        return;

    style.foreground = value;
    emit foregroundChanged();
}

void StreamingServiceStyleModel::setPrimary(const QString& value) {
    if (value == style.primary)
        return;

    style.primary = value;
    emit primaryChanged();
}

void StreamingServiceStyleModel::setPrimaryForeground(const QString& value) {
    if (value == style.primaryForeground)
        return;

    style.primaryForeground = value;
    emit primaryForegroundChanged();
}

void StreamingServiceStyleModel::setSecondary(const QString& value) {
    if (value == style.secondary)
        return;

    style.secondary = value;
    emit secondaryChanged();
}

void StreamingServiceStyleModel::setSecondaryForeground(const QString& value) {
    if (value == style.secondaryForeground)
        return;

    style.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void StreamingServiceStyleModel::updateStyle(const StreamingServiceStyle& newStyle) {
    setTheme(newStyle.theme);
    setAccent(newStyle.accent);
    setBackground(newStyle.background);
    setForeground(newStyle.foreground);
    setPrimary(newStyle.primary);
    setPrimaryForeground(newStyle.primaryForeground);
    setSecondary(newStyle.secondary);
    setSecondaryForeground(newStyle.secondaryForeground);
}

double StreamingServiceStyleModel::getColorScaleFactor(const QString& color) {
    if (QColor(color).lightness() > 164)
        return 1.05;
    return 1.2;
}

bool StreamingServiceStyleModel::isDark(const QString &color) {
    return QColor(color).lightness() < 164;
}



