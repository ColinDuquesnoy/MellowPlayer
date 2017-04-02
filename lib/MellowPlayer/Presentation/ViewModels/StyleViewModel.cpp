#include <MellowPlayer/UseCases/Plugin/Plugin.hpp>
#include <MellowPlayer/UseCases/Plugin/PluginManager.hpp>
#include "StyleViewModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StyleViewModel::StyleViewModel(PluginManager& pluginManager) :
        usePluginStyle(true),
        style(PluginStyle::defaultStyle()),
        pluginManager(pluginManager) {
    connect(&pluginManager, &PluginManager::currentPluginChanged, this, &StyleViewModel::onPluginChanged);
}

QString StyleViewModel::getTheme() const {
    return style.theme;
}

QString StyleViewModel::getAccent() const {
    return style.accent;
}

QString StyleViewModel::getBackground() const {
    return style.background;
}

QString StyleViewModel::getForeground() const {
    return style.foreground;
}

QString StyleViewModel::getPrimary() const {
    return style.primary;
}

QString StyleViewModel::getPrimaryForeground() const {
    return style.primaryForeground;
}

QString StyleViewModel::getSecondary() const {
    return style.secondary;
}

QString StyleViewModel::getSecondaryForeground() const {
    return style.secondaryForeground;
}

bool StyleViewModel::getUsePluginStyle() const {
    return usePluginStyle;
}

void StyleViewModel::setUsePluginStyle(bool value) {
    if (value == usePluginStyle)
        return;

    usePluginStyle = value;
    emit usePluginStyleChanged();

    Plugin* currentPlugin = pluginManager.getCurrent();
    if (usePluginStyle && currentPlugin != nullptr)
        updateStyle(currentPlugin->getStyle());
    else
        updateStyle(PluginStyle::defaultStyle());
}

void StyleViewModel::onPluginChanged(Plugin* plugin) {
    if (plugin != nullptr)
        updateStyle(plugin->getStyle());
}

void StyleViewModel::setTheme(const QString& value) {
    if (value == style.theme)
        return;

    style.theme = value;
    emit themeChanged();
}

void StyleViewModel::setAccent(const QString& value) {
    if (value == style.accent)
        return;

    style.accent = value;
    emit accentChanged();
}

void StyleViewModel::setBackground(const QString& value) {
    if (value == style.background)
        return;

    style.background = value;
    emit backgroundChanged();
}

void StyleViewModel::setForeground(const QString& value) {
    if (value == style.foreground)
        return;

    style.foreground = value;
    emit foregroundChanged();
}

void StyleViewModel::setPrimary(const QString& value) {
    if (value == style.primary)
        return;

    style.primary = value;
    emit primaryChanged();
}

void StyleViewModel::setPrimaryForeground(const QString& value) {
    if (value == style.primaryForeground)
        return;

    style.primaryForeground = value;
    emit primaryForegroundChanged();
}

void StyleViewModel::setSecondary(const QString& value) {
    if (value == style.secondary)
        return;

    style.secondary = value;
    emit secondaryChanged();
}

void StyleViewModel::setSecondaryForeground(const QString& value) {
    if (value == style.secondaryForeground)
        return;

    style.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void StyleViewModel::updateStyle(const PluginStyle& newStyle) {
    setTheme(newStyle.theme);
    setAccent(newStyle.accent);
    setBackground(newStyle.background);
    setForeground(newStyle.foreground);
    setPrimary(newStyle.primary);
    setPrimaryForeground(newStyle.primaryForeground);
    setSecondary(newStyle.secondary);
    setSecondaryForeground(newStyle.secondaryForeground);
}

double StyleViewModel::getColorScaleFactor(const QString& color) {
    if (QColor(color).lightness() > 128)
        return 1.05;
    return 1.2;
}



