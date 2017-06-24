#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include "StreamingServiceStyleModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServiceStyleModel::StreamingServiceStyleModel(StreamingServices& streamingServices, Settings& settings) :
        useServiceStyle(true),
        streamingServices(streamingServices),
        accentColorSetting(settings.get(SettingKey::APPEARANCE_ACCENT)),
        adaptiveThemeSetting(settings.get(SettingKey::APPEARANCE_ADAPTIVE_THEME)),
        backgroundSetting(settings.get(SettingKey::APPEARANCE_BACKGROUND)),
        foregroundSetting(settings.get(SettingKey::APPEARANCE_FOREGROUND)),
        primaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_BACKGROUND)),
        primaryForegroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_FOREGROUND)),
        secondaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_BACKGROUND)),
        secondaryForegroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_FOREGROUND)),
        style(getDefaultStyle()) {
    connect(&streamingServices, &StreamingServices::currentChanged, this,
            &StreamingServiceStyleModel::onCurrentServiceChanged);
    connect(&accentColorSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&adaptiveThemeSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&backgroundSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&foregroundSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&primaryBackgroundSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&primaryForegroundSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&secondaryBackgroundSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
    connect(&secondaryForegroundSetting, &Setting::valueChanged, this, &StreamingServiceStyleModel::updateStyle);
}

QString StreamingServiceStyleModel::getTheme() const {
    return isDark(style.background) ? "dark" : "light";
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

bool StreamingServiceStyleModel::getUseServiceStyle() const {
    return useServiceStyle;
}

void StreamingServiceStyleModel::setUseServiceStyle(bool value) {
    if (value == useServiceStyle)
        return;

    useServiceStyle = value;
    emit useServiceStyleChanged();
    updateStyle();
}

void StreamingServiceStyleModel::updateStyle() {
    StreamingService* currentService = streamingServices.getCurrent();
    if (useServiceStyle && currentService != nullptr && adaptiveThemeSetting.getValue().toBool() &&
            !currentService->getStyle().isEmpty())
        fromStyle(currentService->getStyle());
    else
        fromStyle(getDefaultStyle());
}

void StreamingServiceStyleModel::onCurrentServiceChanged(StreamingService* streamingService) {
    if (streamingService != nullptr)
        updateStyle();
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
    emit themeChanged();
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

void StreamingServiceStyleModel::fromStyle(const StreamingServiceStyle& newStyle) {
    setAccent(newStyle.accent);
    setBackground(newStyle.background);
    setForeground(newStyle.foreground);
    setPrimary(newStyle.primary);
    setPrimaryForeground(newStyle.primaryForeground);
    setSecondary(newStyle.secondary);
    setSecondaryForeground(newStyle.secondaryForeground);
}

double StreamingServiceStyleModel::getColorScaleFactor(const QString& color) const {
    if (QColor(color).lightness() > 164)
        return 1.05;
    return 1.2;
}

bool StreamingServiceStyleModel::isDark(const QString &color) const {
    return QColor(color).lightness() < 164;
}

StreamingServiceStyle StreamingServiceStyleModel::getDefaultStyle() {
    return StreamingServiceStyle {
            accentColorSetting.getValue().toString(),
            backgroundSetting.getValue().toString(),
            foregroundSetting.getValue().toString(),
            primaryBackgroundSetting.getValue().toString(),
            primaryForegroundSetting.getValue().toString(),
            secondaryBackgroundSetting.getValue().toString(),
            secondaryForegroundSetting.getValue().toString()
    };
}
